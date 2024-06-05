#include "Player.h"
#include "Math.h"
#include "FireBall.h"
#include "iostream"
#include "TileMap.h"
#include "Trap.h"
#include "Shield.h"
#include "Enemy.h"

Player::Player() : maxFireRate(400), startPositionX(100), startPositionY(100) {
    maxHealth = 100;
    health = maxHealth;
    healthBar.setSize(sf::Vector2f(50.0f, 5.0f));
    healthBar.setFillColor(sf::Color::Green);

    healthBarBackground.setSize(sf::Vector2f(50.0f, 5.0f));
    healthBarBackground.setFillColor(sf::Color::Red);
}

int Player::GetHealth() const {
    return health;
}

void Player::SetHealth(int h) {
    health = h;
}


void Player::Respawn() {
    sprite.setPosition(startPositionX, startPositionY);
    health = 100;
}

void Player::Initialize() {
    bounding_rect.setFillColor(sf::Color::Transparent);
    bounding_rect.setOutlineColor(sf::Color::Red);
    bounding_rect.setOutlineThickness(2);
    sprite.setPosition(startPositionX, startPositionY);

}

void Player::HandleTrapCollision() {
    if (!shield.IsActive()) {
        health -= 50;
        if (health <= 0) {
            Respawn();
        }
    }
    else  {
        std::cout << "Shield absorbed the damage!" << std::endl;
    }
}


void Player::Load() {

    texture.loadFromFile("C:/Users/D/CLionProjects/Game_1/assets/main_character/textures/AnimationSheet_Character.png");

    sprite.setTexture(texture);
    X_index = 0;
    Y_index = 0;

    sprite.setTextureRect(sf::IntRect(X_index * size.x, Y_index * size.y, size.x, size.y));
    sprite.scale(3, 3);

    size = sf::Vector2i(32, 32);
    bounding_rect.setSize(sf::Vector2f(size.x * 3, size.y * 3));
    ;
}

void Player::Update(float& frame, float& time, Enemy& enemy, float deltaTime, sf::Vector2f &mousePosition, const std::vector<TileObject>& objects, const std::vector<Trap>& traps) {

    fireRateTimer += deltaTime;
    jumpTimer += deltaTime;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
        shield.Activate();
    }

    shield.Update(deltaTime / 1000.0f);

    for (const auto& trap : traps) {
        if (Math::IsCollisionHappen(sprite.getGlobalBounds(), trap.getSprite().getGlobalBounds())) {
            if (sprite.getPosition().y + sprite.getGlobalBounds().height <= trap.getPosition().y + 5) {
                std::cout << "Collision with Trap from above" << std::endl;
                if (shield.IsActive()) {
                    verticalSpeed = -9.0f;
                    onGround = false;
                    shield.TurnOffShield();
                } else {
                    HandleTrapCollision();
                }
            }
        }
    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && fireRateTimer >= maxFireRate){

        container_of_fireball.push_back(FireBall("C:/Users/D/CLionProjects/Game_1/assets/main_character/textures/Firebolt_SpriteSheet.png"));
        int i = container_of_fireball.size() - 1;
        //------------------------------------------
        container_of_fireball[i].Initialize(sprite.getPosition(), mousePosition, fireBallSpeed);
        fireRateTimer = 0;
    }

    for(int i = 0; i < container_of_fireball.size(); i++){
        container_of_fireball[i].Update(deltaTime);
        //COLLISION

        if(enemy.health > 0){
            if(Math::IsCollisionHappen(container_of_fireball[i].GetGlobalBounds(), enemy.sprite.getGlobalBounds())){
                enemy.ChangeHealth(-20);
                container_of_fireball.erase(container_of_fireball.begin() + i);
                std::cout << "Skeleton health:" << enemy.health << std::endl;

            }
        }
    }

    sf::Vector2f moveDirection(0, 0);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        Y_index = 3;
        moveDirection.x += PlayerSpeed * deltaTime;
        frame += 0.01 * deltaTime;
        if(frame > 8){
            frame -= 8;
        }
        sprite.setTextureRect(sf::IntRect((32) * (int)frame, Y_index * 32, 32, 32));
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        Y_index = 3;
        moveDirection.x -= PlayerSpeed * deltaTime;
        frame += 0.01 * time;
        if(frame > 8){
            frame -= 8;
        }
        sprite.setTextureRect(sf::IntRect((32) * (int)frame + 32, Y_index * 32, -32, 32));
    }

    else{
        Y_index = 0;
        frame += 0.002 * deltaTime;
        if(frame > 2){
            frame -= 2;
        }
        sprite.setTextureRect(sf::IntRect((32) * (int)frame, Y_index * 32, 32, 32));
    }

    if (onGround && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        verticalSpeed = jumpVelocity;
        onGround = false;
        isJumping = true;
    }

    if (!onGround) {
        verticalSpeed += gravity;
        moveDirection.y += verticalSpeed;
        if (sprite.getPosition().y + moveDirection.y >= 900) {
            moveDirection.y = 750 - sprite.getPosition().y;
            onGround = true;
            verticalSpeed = 0;
        }

    }

    onGround = false;

    Math::handleHorizontalCollisions(sprite, moveDirection, objects);
    sprite.move(moveDirection.x, 0);

    Math::handleVerticalCollisions(sprite, moveDirection, objects, onGround, verticalSpeed);
    sprite.move(0, moveDirection.y);

    bounding_rect.setPosition(sprite.getPosition());

    if (Math::IsCollisionHappen(sprite.getGlobalBounds(), enemy.sprite.getGlobalBounds())) {
        std::cout << "Collision with Skeleton" << std::endl;
        sf::Vector2f pushDirection = sprite.getPosition() - enemy.sprite.getPosition();
        float pushDistance = 1.0f;
        if (pushDirection.x > 0) {
            sprite.move(pushDistance, 0);
        } else {
            sprite.move(-pushDistance, 0);
        }
    }

    for (const auto& trap : traps) {
        if (Math::IsCollisionHappen(sprite.getGlobalBounds(), trap.getSprite().getGlobalBounds())) {
            HandleTrapCollision();
        }
    }

    healthBar.setSize(sf::Vector2f((static_cast<float>(health) / maxHealth) * 50.0f, 5.0f));
    healthBar.setPosition(sprite.getPosition().x, sprite.getPosition().y - 10);
    healthBarBackground.setPosition(sprite.getPosition().x, sprite.getPosition().y - 10);


}

void Player::Draw(sf::RenderWindow& window){

    window.draw(sprite);
//    window.draw(bounding_rect);
    shield.Draw(window, sprite.getPosition());

    for(int i = 0; i < container_of_fireball.size(); i++){
        container_of_fireball[i].Draw(window);
    }

    window.draw(healthBarBackground);
    window.draw(healthBar);

}