//
// Created by bparsy on 1/15/21.
//

#ifndef FSDRAW_ENGINE_HH
#define FSDRAW_ENGINE_HH


#include <SFML/Graphics.hpp>

class Engine {
public:
    Engine(unsigned w, unsigned h);
    void update_time();
    [[nodiscard]] auto dt() const -> float;

    void run(std::string const& drawpath,
             unsigned chain_size = 100,
             unsigned interpolation = 0,
             float seconds_per_round = 10.f);

private:
    unsigned w_, h_;
    sf::Time dt_;
    sf::Font font_;
    sf::Text tl_text_;
};


#endif //FSDRAW_ENGINE_HH
