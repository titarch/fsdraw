#include <SFML/Graphics.hpp>
#include <shapes/Arrow.hh>

int main() {
    sf::ContextSettings settings{};
    settings.antialiasingLevel = 16;

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "sfml-fsdraw", sf::Style::Default, settings);
    Arrow arrow({0, 0}, {1920, 1080});
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(arrow);
        window.display();
    }

    return 0;
}