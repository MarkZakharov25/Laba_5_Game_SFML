#pragma once

#ifndef GAME_1_MATH_H
#define GAME_1_MATH_H
#include "SFML/Graphics.hpp"
#include "TileMap.h"


class Math {
public:
    static sf::Vector2f NormalizeVector(sf::Vector2f vector);
    static bool IsCollisionHappen(sf::FloatRect  rect1, sf::FloatRect rect2);
    static void handleHorizontalCollisions(sf::Sprite& sprite, sf::Vector2f& moveDirection, const std::vector<TileObject>& objects);
    static void handleVerticalCollisions(sf::Sprite& sprite, sf::Vector2f& moveDirection, const std::vector<TileObject>& objects, bool& onGround, float& verticalSpeed);
};



#endif //GAME_1_MATH_H
