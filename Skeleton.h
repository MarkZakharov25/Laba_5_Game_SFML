#pragma once

#ifndef GAME_1_SKELETON_H
#define GAME_1_SKELETON_H

#include <SFML/Graphics.hpp>


class Skeleton {
private:
    sf::Texture texture;
    int X_index;
    int Y_index;
    sf::Vector2i size;

    sf::RectangleShape bounding_rect;

public:
    sf::Sprite sprite;
    void Initialize();
    void Load();
    void Update();
    void Draw(sf::RenderWindow& window);

};


#endif //GAME_1_SKELETON_H
