#pragma once

#ifndef GAME_1_PLAYER_H
#define GAME_1_PLAYER_H

#include <SFML/Graphics.hpp>
#include "Skeleton.h"


class Player {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    int X_index;
    int Y_index;
    sf::Vector2i size;
    //---------------------------------------------------------------------------
    sf::Texture texture_fireball;
    sf::Sprite sprite_fireball;
    std::vector<sf::Sprite> container_of_fireball;

    sf::RectangleShape bounding_rect;

public:
    void Initialize();
    void Load();
    void Update(float& frame, float& time, Skeleton& skeleton);
    void Draw(sf::RenderWindow& window);


};


#endif //GAME_1_PLAYER_H
