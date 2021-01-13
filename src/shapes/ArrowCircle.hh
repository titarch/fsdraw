//
// Created by bparsy on 1/12/21.
//

#ifndef FSDRAW_ARROWCIRCLE_HH
#define FSDRAW_ARROWCIRCLE_HH


#include "Arrow.hh"

class ArrowCircle : public Arrow {
public:
    ArrowCircle();
    ArrowCircle(sf::Vector2f const& start, sf::Vector2f const& end);
    ArrowCircle(float radius, float angle);
    ~ArrowCircle() override = default;

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::CircleShape circle_;
};


#endif //FSDRAW_ARROWCIRCLE_HH
