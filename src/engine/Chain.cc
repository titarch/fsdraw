//
// Created by bparsy on 1/12/21.
//

#include "Chain.hh"

void Chain::emplace_arrow(float radius, float angle) {
    arrows_.emplace_back(radius, angle);
}

void Chain::step(float angle) {
    auto sign = 1;
    for (auto i = 0u; i < arrows_.size(); ++i, sign = -sign)
        arrows_[i].rotate(sign * angle * i);
    update_origins();
}

void Chain::update_origins() {
    if (arrows_.empty()) return;

    arrows_.front().setPosition(getPosition());
    for (auto i = 1u; i < arrows_.size(); ++i)
        arrows_[i].setPosition(arrows_[i - 1].tip_position());
    trail_.add_point(arrows_.back().tip_position());
}

void Chain::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform = getTransform();

    for (auto const& arrow : arrows_)
        target.draw(arrow, states);
    target.draw(trail_, states);
}
