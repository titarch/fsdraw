//
// Created by bparsy on 1/12/21.
//

#ifndef FSDRAW_ARROW_HH
#define FSDRAW_ARROW_HH


#include <SFML/Graphics.hpp>

class Arrow : public sf::Drawable, public sf::Transformable {
public:
    Arrow();
    Arrow(sf::Vector2f const& start, sf::Vector2f const& end);
    ~Arrow() override = default;

    [[nodiscard]] auto tip_position() const -> sf::Vector2f;

    void set_color(sf::Color const& color);
protected:
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    float edge2tip_ratio_{0.9f};
    float edge_thickness_{0.01f}, tip_thickness_{0.1f};
    sf::Color color_{sf::Color::White};

    sf::VertexArray vertices_;
};


#endif //FSDRAW_ARROW_HH
