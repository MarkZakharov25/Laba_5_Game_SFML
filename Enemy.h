#pragma once

#ifndef GAME_1_ENEMY_H
#define GAME_1_ENEMY_H


#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "TileMap.h"
#include "Math.h"
#include "Player.h"

class Player;

class Enemy {

public:
    sf::Sprite sprite;
    int health;

public:
    Enemy(const std::string& textureFile, const sf::Vector2i& size, int frames, int moveDistance, int health);

    void Initialize();
    void Load();
    void Update(float& deltaTime, const std::vector<TileObject>& objects, float& frame, const sf::Vector2f& playerPosition, Player& player);
    void Draw(sf::RenderWindow &window) const;
    void ChangeHealth(int hp);

private:
    sf::Texture texture;
    sf::RectangleShape bounding_rect;
    sf::Font font;
    sf::Text healthText;
    sf::Vector2i size;
    int frames;
    int moveDistance;
    int distanceMoved;
    int direction;
    bool isAttacking;
    float attackCooldown;
    float verticalSpeed;
    float gravity;
    bool onGround;
    int X_index;
    int Y_index;
};



#endif //GAME_1_ENEMY_H
