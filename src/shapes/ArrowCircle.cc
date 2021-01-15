//
// Created by bparsy on 1/12/21.
//

#include <utils/vectormath.hh>
#include "ArrowCircle.hh"

ArrowCircle::ArrowCircle() : Arrow(), circle_(1.f, 100) {
    circle_.setFillColor(sf::Color::Transparent);
    circle_.setOutlineThickness(0.01f);
    circle_.setOrigin(1.f, 1.f);
}

ArrowCircle::ArrowCircle(const sf::Vector2f& start, const sf::Vector2f& end) : ArrowCircle() {
    setPosition(start);
    const auto vect = end - start;
    const auto scale = vm::magnitude(vect);
    const auto angle = std::atan2(vect.y, vect.x) * 180 / vm::pi;

    setScale(scale, scale);
    setRotation(angle);
}

ArrowCircle::ArrowCircle(float radius, float angle) : ArrowCircle(sf::Vector2f{}, vm::altov(radius, angle)) {}

ArrowCircle::ArrowCircle(float radius, float angle, sf::Color const& arrow_color, sf::Color const& circle_color)
        : ArrowCircle(radius, angle) {
    set_arrow_color(arrow_color);
    set_circle_color(circle_color);
}

void ArrowCircle::set_arrow_color(const sf::Color& color) {
    set_color(color);
}

void ArrowCircle::set_circle_color(const sf::Color& color) {
    circle_.setOutlineColor(color);
}

void ArrowCircle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform = getTransform();

    target.draw(vertices_, states);
    target.draw(circle_, states);
}
