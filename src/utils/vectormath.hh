//
// Created by bparsy on 1/12/21.
//

#ifndef FSDRAW_VECTORMATH_HH
#define FSDRAW_VECTORMATH_HH

#include <cmath>
#include <numbers>
#include <SFML/Graphics.hpp>

namespace vm {

    inline constexpr auto pi = std::numbers::pi_v<float>;

    // altov = angle-length to vector (coordinates)
    inline auto altov(float length, float angle) -> sf::Vector2f {
        return length * sf::Vector2f{std::cos(angle), std::sin(angle)};
    }

    inline auto sqrMagnitude(sf::Vector2f const& v) -> float {
        return v.x * v.x + v.y * v.y;
    }

    inline auto magnitude(sf::Vector2f const& v) -> float {
        return std::sqrt(sqrMagnitude(v));
    }

    inline auto sqrDistance(sf::Vector2f const& x, sf::Vector2f const& y) -> float {
        return sqrMagnitude(y - x);
    }

    inline auto distance(sf::Vector2f const& x, sf::Vector2f const& y) -> float {
        return magnitude(y - x);
    }

    template<bool SHOW_PREVIEW = false>
    inline void normalize2D(std::vector<sf::Vector2<double>>& pic) {
        double min_x = std::numeric_limits<double>::infinity();
        double min_y = min_x;
        double max_x = -min_x;
        double max_y = max_x;

        for (auto const& coord : pic) {
            if (coord.x < min_x) min_x = coord.x;
            if (coord.y < min_y) min_y = coord.y;
            if (coord.x > max_x) max_x = coord.x;
            if (coord.y > max_y) max_y = coord.y;
        }

        const auto dx = max_x - min_x;
        const auto dy = max_y - min_y;
        const auto dhmax = std::max(dx, dy) / 2.0;

        for (auto& coord : pic) {
            coord.x = (coord.x - (max_x + min_x) / 2.0) / dhmax;
            coord.y = (coord.y - (max_y + min_y) / 2.0) / dhmax;
        }

        if constexpr (SHOW_PREVIEW) {
            sf::VertexArray vs(sf::LineStrip);
            unsigned i = 0;
            for (auto const& coord : pic) {
                double x = (coord.x + 1.0) * 1080.0 / 2.0;
                double y = (coord.y + 1.0) * 1080.0 / 2.0;
                sf::Uint8 c = unsigned(128 * double(i++) / pic.size()) + 128;
                vs.append(sf::Vertex(sf::Vector2f(x, y), sf::Color(c, c, c)));
            }

            sf::RenderWindow window(sf::VideoMode(1080, 1080), "sfml-what");
            while (window.isOpen()) {
                sf::Event event{};
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }

                window.clear();
                window.draw(vs);
                window.display();

            }
        }
    }

}

#endif //FSDRAW_VECTORMATH_HH
