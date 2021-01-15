//
// Created by bparsy on 1/12/21.
//

#ifndef FSDRAW_CHAIN_HH
#define FSDRAW_CHAIN_HH


#include <complex>
#include "shapes/ArrowCircle.hh"
#include "shapes/Trail.hh"

class Chain : public sf::Drawable, public sf::Transformable {
public:
    Chain() = default;
    Chain(std::initializer_list<std::array<float, 2>> const& init_list);
    ~Chain() override = default;
    void emplace_arrow(float radius, float angle);
    void emplace_arrow(std::complex<double> const& c);
    void step(float dt, float time_per_round);
    void clear_trail();
    void remove_last();
    [[nodiscard]] auto next_n() const -> int;
    [[nodiscard]] auto time() const -> double;
    [[nodiscard]] auto tip_position() const -> sf::Vector2f;
protected:
    void update_origins();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    std::vector<ArrowCircle> arrows_{};
    Trail trail_{};
    double time_{};
};


#endif //FSDRAW_CHAIN_HH
