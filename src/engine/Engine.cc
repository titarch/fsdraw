//
// Created by bparsy on 1/15/21.
//

#include <iostream>
#include "Engine.hh"
#include "Path.hh"

Engine::Engine(unsigned int w, unsigned int h) : w_(w), h_(h), dt_(), font_(), tl_text_() {
    const std::string ttf = "/usr/share/fonts/TTF/Arial.TTF";
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

void Engine::run(std::string const& drawpath, unsigned chain_size, unsigned interpolation, float seconds_per_round) {
    sf::ContextSettings settings{};
    settings.antialiasingLevel = 16;

    sf::RenderWindow window(sf::VideoMode(w_, h_), "sfml-fsdraw", sf::Style::Default, settings);
    auto path = Path::from_plain("../res/paths/" + drawpath + ".txt", 0.45f * float(h_));
    if (interpolation > 0)
        path.linear_interpolation(interpolation);
    auto chain = path.chain(chain_size);
    chain.setPosition(float(w_) / 2, float(h_) / 2);

    sf::View base_view = window.getDefaultView();
    sf::View zoom_view = window.getDefaultView();
    zoom_view.setViewport(sf::FloatRect(0.75f, 0.f, 0.25f, 0.25f));

    float speed_multiplier = 1.0f;
    float speed_increment = 0.1f;
    bool toggle_zoom = true;
    bool toggle_text = true;
    float zoom_factor = 0.05f;
    zoom_view.zoom(zoom_factor);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        window.close();
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
                    default:
                        break;
                }
            }
        }
        window.clear();
        window.setView(base_view);
        window.draw(chain);
        if (toggle_text) {
            char text[256];
            sprintf(text, "speed multiplier = %lfx\nspeed increment = %lf\nfull drawing = %.2lfs\nzoom factor = %lfx",
                    speed_multiplier, speed_increment, seconds_per_round / speed_multiplier, zoom_factor);
            tl_text_.setString(text);
            window.draw(tl_text_);
        }
        if (toggle_zoom) {
            zoom_view.setCenter(chain.tip_position());
            window.setView(zoom_view);
            window.draw(chain);
        }
        window.display();

        chain.step(dt(), seconds_per_round / speed_multiplier);
        update_time();
    }
}