#include "FireBall.h"
#include "Math.h"

FireBall::FireBall(std::string filename) : speed(0) {
    texture_fireball.loadFromFile(filename);
    sprite_fireball.setTexture(texture_fireball);
    sprite_fireball.setTextureRect(sf::IntRect(0, 0, 50, 48 ));
}


void FireBall::Initialize(const sf::Vector2f& position, sf::Vector2f& target, float speed) {

    sprite_fireball.scale(3, 3);
    sprite_fireball.setPosition(position);
    direction = Math::NormalizeVector(target - position);
    this->speed = speed;
}

void FireBall::Update(float deltaTime) {
    sprite_fireball.setPosition(sprite_fireball.getPosition() + direction * speed * deltaTime);
}

void FireBall::Draw(sf::RenderWindow &window) {
    window.draw(sprite_fireball);
}