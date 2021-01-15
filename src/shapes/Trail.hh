//
// Created by bparsy on 1/12/21.
//

#ifndef FSDRAW_TRAIL_HH
#define FSDRAW_TRAIL_HH


#include <SFML/Graphics.hpp>

class Trail : public sf::Drawable, public sf::Transformable {
public:
    Trail();
    ~Trail() override = default;

    void add_point(sf::Vector2f const& pos);
    void clear();
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::VertexArray vertices_;
    std::vector<double> hot_;
};


#endif //FSDRAW_TRAIL_HH
