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
    inline auto altov(float angle, float length) -> sf::Vector2f {
        return length * sf::Vector2f{std::cos(angle), std::sin(angle)};
    }

    inline auto sqrMagnitude(sf::Vector2f const& v) -> float {
        return v.x * v.x + v.y * v.y;
    }

    inline auto magnitude(sf::Vector2f const& v) -> float {
        return std::sqrt(sqrMagnitude(v));
    }
}

#endif //FSDRAW_VECTORMATH_HH
