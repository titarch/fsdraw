//
// Created by bparsy on 1/12/21.
//

#include "Chain.hh"

Chain::Chain(const std::initializer_list<std::array<float, 2>>& init_list) {
    for (auto const& arr : init_list)
        emplace_arrow(arr[0], arr[1]);
}

void Chain::emplace_arrow(float radius, float angle) {
    arrows_.emplace_back(radius, angle, sf::Color(128, 255, 255, 128));
}

void Chain::step(float angle) {
    for (auto i = 0u; i < arrows_.size(); ++i) {
        const int k = int(i+1) / 2 * (i % 2 == 0 ? 1 : -1);
        arrows_[i].rotate(float(k) * angle);
    }
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
