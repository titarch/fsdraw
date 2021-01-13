//
// Created by bparsy on 1/12/21.
//

#include "Trail.hh"

Trail::Trail() : vertices_(sf::LineStrip) {}

void Trail::add_point(const sf::Vector2f& pos) {
    vertices_.append(sf::Vertex(pos, sf::Color::Yellow));
}

void Trail::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform = getTransform();

    target.draw(vertices_, states);
}
