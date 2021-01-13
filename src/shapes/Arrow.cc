//
// Created by bparsy on 1/12/21.
//

#include <cmath>
#include <utils/vectormath.hh>
#include "Arrow.hh"

Arrow::Arrow()
        : vertices_(sf::VertexArray(sf::Triangles, 9)) {
    update();
}

Arrow::Arrow(const sf::Vector2f& start, const sf::Vector2f& end) : Arrow() {
    setPosition(start);
    const auto vect = end - start;
    const auto scale = vm::magnitude(vect);
    const auto angle = std::atan2(vect.y, vect.x) * 180 / vm::pi;

    setScale(scale, scale);
    setRotation(angle);
}

auto Arrow::tip_position() const -> sf::Vector2f {
    return getPosition() + vm::altov(getScale().x, getRotation() * vm::pi / 180.f);
}

void Arrow::update() {
    const auto half_edge_thickness = edge_thickness_ / 2.f;
    const auto half_tip_thickness = tip_thickness_ / 2.f;

    const auto p0 = sf::Vector2f{0.f, -half_edge_thickness};
    const auto p1 = sf::Vector2f{0.f, half_edge_thickness};
    const auto p2 = sf::Vector2f{edge2tip_ratio_, -half_edge_thickness};
    const auto p3 = sf::Vector2f{edge2tip_ratio_, half_edge_thickness};
    const auto p4 = sf::Vector2f{edge2tip_ratio_, -half_tip_thickness};
    const auto p5 = sf::Vector2f{edge2tip_ratio_, half_tip_thickness};
    const auto p6 = sf::Vector2f{1.f, 0.f};

    vertices_[0] = {p0, color_};
    vertices_[1] = {p1, color_};
    vertices_[2] = {p2, color_};

    vertices_[3] = {p1, color_};
    vertices_[4] = {p2, color_};
    vertices_[5] = {p3, color_};

    vertices_[6] = {p4, color_};
    vertices_[7] = {p5, color_};
    vertices_[8] = {p6, color_};
}

void Arrow::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform = getTransform();

    target.draw(vertices_, states);
}
