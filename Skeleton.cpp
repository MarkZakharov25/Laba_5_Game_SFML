#include "Skeleton.h"
#include "Math.h"

Skeleton::Skeleton() :
    health(50),
    verticalSpeed(0),
    gravity(0.98f),
    onGround(false),
    X_index(0),
    Y_index(0),
    direction(1),
    distanceMoved(0),
    moveDistance(300),
    isAttacking(false) {}

void Skeleton::Initialize() {
    bounding_rect.setFillColor(sf::Color::Transparent);
    bounding_rect.setOutlineColor(sf::Color::Green);
    bounding_rect.setOutlineThickness(2);
    size = sf::Vector2i(24, 37);
    //--------------------------------------------------
    font.loadFromFile("C:/Users/D/CLionProjects/Game_1/assets/fonts/Ultragonic.otf");
    healthText.setFont(font);
    healthText.setFillColor(sf::Color::White);
    healthText.setString(std::to_string(health));


}

void Skeleton::Load() {

    sprite.setPosition(2500, 300);
    X_index = 0;
    Y_index = 0;


    bounding_rect.setSize(sf::Vector2f(size.x * 7, size.y * 7));


    texture.loadFromFile("C:/Users/D/CLionProjects/Game_1/assets/Enemies/Skeleton/textures/spritesheet.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(X_index*0, Y_index * 0, 22, 37));

    sprite.scale(7, 7);


}

void Skeleton::Update(float& deltaTime, const std::vector<TileObject>& objects, float& frame, const sf::Vector2f& playerPosition) {
    if (health > 0) {

        sf::Vector2f moveDirection(0, 0);

        float distanceToPlayer = std::abs(sprite.getPosition().x - playerPosition.x);

        if (distanceToPlayer < 300.0f) {
            isAttacking = true;
            Y_index = 0;

            frame += 0.015f * deltaTime;
            if (frame >= 18) {
                frame = 0;
            }
            sprite.setTextureRect(sf::IntRect(43 * (int)frame + 43, Y_index * 37, -43, 37));
        } else {
            isAttacking = false;

            moveDirection.x = direction * 0.25f * deltaTime;
            Y_index = 5;

            frame += 0.01f * deltaTime;
            if (frame >= 11) {
                frame = 0;
            }

            if (direction == 1) {
                sprite.setTextureRect(sf::IntRect(22 * (int)frame, Y_index * 37, 22, 37));
            } else {
                sprite.setTextureRect(sf::IntRect(22 * ((int)frame + 1), Y_index * 37, -22, 37));
            }

            distanceMoved += abs(moveDirection.x);
            if (distanceMoved >= moveDistance) {
                direction = -direction;
                distanceMoved = 0;
            }
        }



        if (!onGround) {
            verticalSpeed += gravity;
            moveDirection.y += verticalSpeed;
        }

        onGround = false;

        Math::handleVerticalCollisions(sprite, moveDirection, objects, onGround, verticalSpeed);
        sprite.move(moveDirection);

        if (onGround) {
            verticalSpeed = 0;
        }

        bounding_rect.setPosition(sprite.getPosition());
        healthText.setPosition(sprite.getPosition() + sf::Vector2f(size.x * 5, 0));
    }
}



void Skeleton::Draw(sf::RenderWindow &window) {

    if(health > 0){
        window.draw(sprite);
        window.draw(bounding_rect);
        window.draw(healthText);
    }


}

void Skeleton::ChangeHealth(int hp){
    health += hp;
    healthText.setString(std::to_string(health));
}