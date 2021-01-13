#include <SFML/Graphics.hpp>
#include <utils/vectormath.hh>
#include "engine/Path.hh"

int main() {
    sf::ContextSettings settings{};
    settings.antialiasingLevel = 16;

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "sfml-fsdraw", sf::Style::Default, settings);
    auto path = Path::from_plain("../res/paths/note.txt");
    auto chain = path.chain(100);
    chain.setPosition(960, 540);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        chain.step(0.005f);

        window.clear();
        window.draw(chain);
        window.display();
    }

    return 0;
}