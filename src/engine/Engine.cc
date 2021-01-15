//
// Created by bparsy on 1/15/21.
//

#include "Engine.hh"
#include "Path.hh"

Engine::Engine(unsigned int w, unsigned int h) : w_(w), h_(h), dt_() {}

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
    zoom_view.zoom(0.02f);

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
                    default:
                        break;
                }
            }
        }
        window.clear();
        window.setView(base_view);
        window.draw(chain);
        zoom_view.setCenter(chain.tip_position());
        window.setView(zoom_view);
        window.draw(chain);
        window.display();

        chain.step(dt(), seconds_per_round);
        update_time();
    }
}