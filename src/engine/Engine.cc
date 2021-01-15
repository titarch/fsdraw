//
// Created by bparsy on 1/15/21.
//

#include <iostream>
#include "Engine.hh"
#include "Path.hh"

Engine::Engine(unsigned int w, unsigned int h) : w_(w), h_(h), dt_(), font_(), tl_text_(),
                                                 win_(sf::VideoMode(w, h), "sfml-fsdraw", sf::Style::Default,
                                                      sf::ContextSettings{0, 0, 16}) {
    const std::string ttf = "../res/DejaVuSansMono.ttf";
    if (!font_.loadFromFile(ttf))
        std::cerr << "Could not find: " << ttf;
    tl_text_.setFont(font_);
    tl_text_.setCharacterSize(16);
    tl_text_.setFillColor(sf::Color::White);
}

void Engine::update_time() {
    static sf::Clock clock{};
    dt_ = clock.restart();
}

auto Engine::dt() const -> float {
    return dt_.asSeconds();
}

void Engine::display_help() {
    tl_text_.setCharacterSize(48);
    tl_text_.setString("H (hold): Display help\nS: Decrease speed by increment\nD: Increase speed by increment\n"
                       "A: Scale down increment by 10\nF: Scale up increment by 10\n"
                       "Z: Toggle zoom view display\nT: Toggle text display\n+: Zoom in 25%\n"
                       "-: Zoom out 25%\nR: Clear trail\nQ: Remove a coefficient\nW: Add a coefficient");
    while (win_.isOpen() && sf::Keyboard::isKeyPressed(sf::Keyboard::H)) {
        win_.clear();
        win_.draw(tl_text_);
        win_.display();
    }
    tl_text_.setCharacterSize(16);
    update_time();
}

void Engine::run(std::string const& drawpath, unsigned chain_size, unsigned interpolation, float seconds_per_round) {

    auto path = Path::from_plain("../res/paths/" + drawpath + ".txt", 0.45f * float(h_));
    if (interpolation > 0)
        path.linear_interpolation(interpolation);
    auto chain = path.chain(chain_size);
    chain.setPosition(float(w_) / 2, float(h_) / 2);

    const sf::View base_view = win_.getDefaultView();
    sf::View zoom_view = win_.getDefaultView();
    zoom_view.setViewport(sf::FloatRect(0.75f, 0.f, 0.25f, 0.25f));

    float speed_multiplier = 1.0f;
    float speed_increment = 0.1f;
    bool toggle_zoom = true;
    bool toggle_text = true;
    float zoom_factor = 0.05f;
    zoom_view.zoom(zoom_factor);

    while (win_.isOpen()) {
        sf::Event event{};
        while (win_.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                win_.close();
            else if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        win_.close();
                        break;
                    case sf::Keyboard::H:
                        win_.setView(base_view);
                        display_help();
                        break;
                    case sf::Keyboard::S:
                        speed_multiplier -= speed_increment;
                        break;
                    case sf::Keyboard::D:
                        speed_multiplier += speed_increment;
                        break;
                    case sf::Keyboard::A:
                        speed_increment *= 0.1f;
                        break;
                    case sf::Keyboard::F:
                        speed_increment *= 10.f;
                        break;
                    case sf::Keyboard::Z:
                        toggle_zoom = !toggle_zoom;
                        break;
                    case sf::Keyboard::T:
                        toggle_text = !toggle_text;
                        break;
                    case sf::Keyboard::Add:
                        zoom_factor *= 0.75f;
                        zoom_view.setSize(base_view.getSize() * zoom_factor);
                        break;
                    case sf::Keyboard::Subtract:
                        zoom_factor *= 1.25f;
                        zoom_view.setSize(base_view.getSize() * zoom_factor);
                        break;
                    case sf::Keyboard::R:
                        chain.clear_trail();
                        break;
                    case sf::Keyboard::Q:
                        if (chain_size <= 1) break;
                        --chain_size;
                        chain.remove_last();
                        break;
                    case sf::Keyboard::W:
                        ++chain_size;
                        chain.emplace_arrow(path.fs_coef(chain.next_n()));
                        break;
                    default:
                        break;
                }
            }
        }
        win_.clear();
        win_.setView(base_view);
        win_.draw(chain);
        if (toggle_text) {
            char text[1024];
            sprintf(text,
                    "time = %lf\n"
                    "speed multiplier = %lfx\nspeed increment = %lf\nfull drawing = %.2lfs\n"
                    "zoom factor = %lfx\nNumber of coefficients = %u\nInterpolation level = %u\n"
                    "(hold \"H\" to display help)",
                    chain.time(), speed_multiplier, speed_increment, seconds_per_round / speed_multiplier, zoom_factor,
                    chain_size, interpolation);
            tl_text_.setString(text);
            win_.draw(tl_text_);
        }
        if (toggle_zoom) {
            zoom_view.setCenter(chain.tip_position());
            win_.setView(zoom_view);
            win_.draw(chain);
        }
        win_.display();

        chain.step(dt(), seconds_per_round / speed_multiplier);
        update_time();
    }
}