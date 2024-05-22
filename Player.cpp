#include "Player.h"
#include "Math.h"
#include "FireBall.h"
#include "iostream"
#include "TileMap.h"

Player::Player() : maxFireRate(400) {}

void Player::Initialize() {
    bounding_rect.setFillColor(sf::Color::Transparent);
    bounding_rect.setOutlineColor(sf::Color::Red);
    bounding_rect.setOutlineThickness(2);


}

void Player::Load() {

    texture.loadFromFile("C:/Users/D/CLionProjects/Game_1/assets/main_character/textures/AnimationSheet_Character.png");

    sprite.setTexture(texture);
     X_index = 0;
     Y_index = 0;

    sprite.setTextureRect(sf::IntRect(X_index * size.x, Y_index * size.y, size.x, size.y));
    sprite.scale(5, 5);

    size = sf::Vector2i(32, 32);
    bounding_rect.setSize(sf::Vector2f(size.x * 5, size.y * 5));
    ;
}

void Player::Update(float& frame, float& time, Skeleton& skeleton, float deltaTime, sf::Vector2f &mousePosition, const std::vector<TileObject>& objects) {

    fireRateTimer += deltaTime;
    jumpTimer += deltaTime;

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

        if(skeleton.health > 0){
            if(Math::IsCollisionHappen(container_of_fireball[i].GetGlobalBounds(), skeleton.sprite.getGlobalBounds())){
                skeleton.ChangeHealth(-10);
                container_of_fireball.erase(container_of_fireball.begin() + i);
                std::cout << "Skeleton health:" << skeleton.health << std::endl;

            }
        }
    }

    sf::Vector2f moveDirection(0, 0);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        Y_index = 3;
        moveDirection.x += PlayerSpeed * deltaTime;
        frame += 0.017 * time;
        if(frame > 8){
            frame -= 8;
        }
        sprite.setTextureRect(sf::IntRect((32) * (int)frame, Y_index * 32, 32, 32));
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        Y_index = 3;
        moveDirection.x -= PlayerSpeed * deltaTime;
        frame += 0.015 * time;
        if(frame > 8){
            frame -= 8;
        }
        sprite.setTextureRect(sf::IntRect((32) * (int)frame + 32, Y_index * 32, -32, 32));
    }

    else{
        Y_index = 0;
        frame += 0.003 * time;
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
    handleCollisions(moveDirection, objects);
    sprite.move(moveDirection.x, moveDirection.y);

    bounding_rect.setPosition(sprite.getPosition());

    if(Math::IsCollisionHappen(sprite.getGlobalBounds(), skeleton.sprite.getGlobalBounds())){
        std::cout << "Collision" << std::endl;
    }

}

void Player::handleCollisions(sf::Vector2f& moveDirection, const std::vector<TileObject>& objects) {
    sf::FloatRect playerBounds = sprite.getGlobalBounds();
    playerBounds.left += moveDirection.x;
    for (const auto& object : objects) {
        if (object.name == "solid") {
            sf::FloatRect objectBounds(object.x, object.y, object.width, object.height);
            if (playerBounds.intersects(objectBounds)) {
                if (moveDirection.x > 0) {
                    moveDirection.x = objectBounds.left - playerBounds.left - playerBounds.width;
                } else if (moveDirection.x < 0) {
                    moveDirection.x = objectBounds.left + objectBounds.width - playerBounds.left;
                }
            }
        }
    }

    playerBounds = sprite.getGlobalBounds();
    playerBounds.top += moveDirection.y;
    for (const auto& object : objects) {
        if (object.name == "solid") {
            sf::FloatRect objectBounds(object.x, object.y, object.width, object.height);
            if (playerBounds.intersects(objectBounds)) {
                if (moveDirection.y > 0) {
                    moveDirection.y = objectBounds.top - playerBounds.top - playerBounds.height;
                    onGround = true;
                } else if (moveDirection.y < 0) {
                    moveDirection.y = objectBounds.top + objectBounds.height - playerBounds.top;
                }
                verticalSpeed = 0;
            }
        }
    }
}

void Player::Draw(sf::RenderWindow& window){

    window.draw(sprite);
    window.draw(bounding_rect);

    for(int i = 0; i < container_of_fireball.size(); i++){
        container_of_fireball[i].Draw(window);
    }

}