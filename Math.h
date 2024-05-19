#pragma once

#ifndef GAME_1_MATH_H
#define GAME_1_MATH_H
#include "SFML/Graphics.hpp"


class Math {
public:
    static sf::Vector2f NormalizeVector(sf::Vector2f vector);
    static bool IsCollisionHappen(sf::FloatRect  rect1, sf::FloatRect rect2);
};


#endif //GAME_1_MATH_H
