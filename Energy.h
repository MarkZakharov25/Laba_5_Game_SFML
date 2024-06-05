#pragma once

#ifndef GAME_1_ENERGY_H
#define GAME_1_ENERGY_H

#include <SFML/Graphics.hpp>

class Energy {
public:
    Energy(sf::Vector2f position);

    void Draw(sf::RenderWindow &window);

    sf::FloatRect GetBounds() const;

private:
    sf::RectangleShape shape;
};


#endif //GAME_1_ENERGY_H
