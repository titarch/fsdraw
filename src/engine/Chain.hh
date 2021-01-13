//
// Created by bparsy on 1/12/21.
//

#ifndef FSDRAW_CHAIN_HH
#define FSDRAW_CHAIN_HH


#include "shapes/ArrowCircle.hh"
#include "shapes/Trail.hh"

class Chain : public sf::Drawable, public sf::Transformable {
public:
    Chain() = default;
    Chain(std::initializer_list<std::array<float, 2>> const& init_list);
    ~Chain() override = default;
    void emplace_arrow(float radius, float angle);
    void step(float dt);
protected:
    void update_origins();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    std::vector<ArrowCircle> arrows_{};
    Trail trail_{};
};


#endif //FSDRAW_CHAIN_HH
