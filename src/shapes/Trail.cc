//
// Created by bparsy on 1/12/21.
//

#include <utils/vectormath.hh>
#include "Trail.hh"

Trail::Trail() : vertices_(sf::LineStrip), hot_() {}

void Trail::add_point(const sf::Vector2f& pos) {
    static sf::Vector2f last_pos{};
    if (vm::sqrDistance(pos, last_pos) < 1.f) return;
    last_pos = pos;

    for (auto i = 0u; i < vertices_.getVertexCount(); ++i)
        vertices_[i].color.r = std::clamp(hot_[i] -= 0.1, 0.0, 255.0);
    hot_.push_back(255.0);
    vertices_.append(sf::Vertex(pos, sf::Color::Magenta));
}

void Trail::clear() {
    vertices_.clear();
    hot_.clear();
}

void Trail::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform = getTransform();

    target.draw(vertices_, states);
}
