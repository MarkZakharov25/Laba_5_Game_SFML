#pragma once

#ifndef GAME_1_SKELETON_H
#define GAME_1_SKELETON_H

#include <SFML/Graphics.hpp>
#include "TileMap.h"
#include "Player.h"

class Player;


class Skeleton {
private:
    sf::Texture texture;
    int X_index;
    int Y_index;
    sf::Vector2i size;
    sf::Font font;
    sf::Text healthText;

    //---------------------------
    float verticalSpeed;
    float gravity;
    bool onGround;

    int direction;
    float distanceMoved;
    float moveDistance;

    bool isAttacking;
    float attackCooldown;


    sf::RectangleShape bounding_rect;

public:
    sf::Sprite sprite;
    int health;
public:
    Skeleton();
    void Initialize();
    void Load();
    void Update(float& deltaTime, const std::vector<TileObject>& objects, float& frame, const sf::Vector2f& playerPosition, Player& player);
    void Draw(sf::RenderWindow& window) const;
    void ChangeHealth(int health);

};


#endif //GAME_1_SKELETON_H
