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
    sf::Font font;
    sf::Text healthText;


    sf::RectangleShape bounding_rect;

public:
    sf::Sprite sprite;
    int health;
public:
    Skeleton();
    void Initialize();
    void Load();
    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);
    void ChangeHealth(int health);

};


#endif //GAME_1_SKELETON_H
