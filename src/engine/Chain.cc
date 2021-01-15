//
// Created by bparsy on 1/12/21.
//

#include <utils/vectormath.hh>
#include "Chain.hh"

using namespace std::complex_literals;

Chain::Chain(const std::initializer_list<std::array<float, 2>>& init_list) {
    for (auto const& arr : init_list)
        emplace_arrow(arr[0], arr[1]);
}

void Chain::emplace_arrow(float radius, float angle) {
    arrows_.emplace_back(radius, angle, sf::Color(255, 255, 255, 200), sf::Color(0, 255, 255, 100));
    phases_.push_back(angle);
}

void Chain::emplace_arrow(const std::complex<double>& c) {
    emplace_arrow(std::abs(c), std::arg(c));
}

void Chain::step(float dt, float time_per_round) {
    for (auto i = 0u; i < arrows_.size(); ++i) {
        const int k = int(i + 1) / 2 * (i % 2 == 0 ? 1 : -1);
        arrows_[i].setRotation(std::arg(
                std::exp(1.0i * (double(k) * 2.0 * vm::pi * time_ + phases_[i]))
        ) / vm::pi * 180);
    }
    time_ += dt / time_per_round;
    while (time_ > 1.0) time_ -= 1.0;
    update_origins();
}

void Chain::clear_trail() {
    trail_.clear();
}

void Chain::remove_last() {
    arrows_.pop_back();
}

auto Chain::next_n() const -> int {
    const auto size = arrows_.size();
    return int(size + 1) / 2 * (size % 2 == 0 ? 1 : -1);
}

auto Chain::time() const -> double {
    return time_;
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

auto Chain::tip_position() const -> sf::Vector2f {
    return arrows_.back().tip_position();
}