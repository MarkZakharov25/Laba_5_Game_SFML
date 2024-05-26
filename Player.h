#pragma once

#ifndef GAME_1_PLAYER_H
#define GAME_1_PLAYER_H

#include <SFML/Graphics.hpp>
#include "Skeleton.h"
#include "FireBall.h"
#include "TileMap.h"
#include "Trap.h"
#include "Shield.h"

class Skeleton;

class Player {
private:
    sf::Texture texture;
    int X_index;
    int Y_index;
    float PlayerSpeed = 0.7f;
    float fireBallSpeed = 2.0f;
    float maxFireRate;
    float fireRateTimer = 0;

    //---------------------------------------------------------------------------
    sf::Texture texture_fireball;
    sf::Sprite sprite_fireball;
    std::vector<FireBall> container_of_fireball;
    sf::RectangleShape bounding_rect;


    //-----------------------------------------------------------------------------------
    float jumpVelocity = -9.0f;
    float gravity = 0.1f;
    float verticalSpeed = 0.0f;
    bool isJumping = false;
    bool onGround = true;
    float jumpTimer = 0;
    float maxJumpRate = 300;
    float dx;
    float dy;

    //-------------------------------------------------------------------------------------------------
    int health;
    int startPositionX;
    int startPositionY;

    //-------------------------------------------------------------------------------------
    Shield shield;
    sf::RectangleShape healthBarBackground;
    int maxHealth;
    sf::RectangleShape healthBar;

public:
    Player();
    void Initialize();
    void Load();
    void Update(float& frame, float& time, Skeleton& skeleton, float deltaTime, sf::Vector2f &mousePosition, const std::vector<TileObject>& objects, const std::vector<Trap>& traps);
    void Draw(sf::RenderWindow& window);

    int GetHealth() const;
    void SetHealth(int health);
    void HandleTrapCollision();
    void Respawn();

    const sf::FloatRect GetGlobalBounds() const { return sprite.getGlobalBounds(); }

public:
    sf::Sprite sprite;
    sf::Vector2i size;
    int currentFrame;
    float frameTime;
    float frameDuration;
    int frameCount;


};


#endif //GAME_1_PLAYER_H
