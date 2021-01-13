#include <SFML/Graphics.hpp>
#include <utils/vectormath.hh>
#include "engine/Chain.hh"

int main() {
    sf::ContextSettings settings{};
    settings.antialiasingLevel = 16;

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "sfml-fsdraw", sf::Style::Default, settings);
    Chain chain{};
    chain.setPosition(460, 540);

    for (auto i = 1; i <= 50; ++i)
        chain.emplace_arrow(250.f / i, i * vm::pi / 50);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        chain.step(vm::pi / 720.f);

        window.clear();
        window.draw(chain);
        window.display();
    }

    return 0;
}