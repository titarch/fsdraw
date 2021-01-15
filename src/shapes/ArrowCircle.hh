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
    ArrowCircle(float radius, float angle, sf::Color const& arrow_color, sf::Color const& circle_color);
    ~ArrowCircle() override = default;

    void set_arrow_color(sf::Color const& color);
    void set_circle_color(sf::Color const& color);
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::CircleShape circle_;
};


#endif //FSDRAW_ARROWCIRCLE_HH
