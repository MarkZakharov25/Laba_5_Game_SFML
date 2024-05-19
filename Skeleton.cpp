#include "Skeleton.h"

void Skeleton::Initialize() {
    bounding_rect.setFillColor(sf::Color::Transparent);
    bounding_rect.setOutlineColor(sf::Color::Green);
    bounding_rect.setOutlineThickness(2);
    size = sf::Vector2i(24, 37);

}

void Skeleton::Load() {

    sprite.setPosition(1650, 650);
    X_index = 0;
    Y_index = 0;


    bounding_rect.setSize(sf::Vector2f(size.x * 7, size.y * 7));


    texture.loadFromFile("C:/Users/D/CLionProjects/Game_1/assets/Enemies/Skeleton/textures/Skeleton_Idle.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(X_index*24, Y_index * 37, 24, 37));

    sprite.scale(7, 7);
}

void Skeleton::Update() {

    bounding_rect.setPosition(sprite.getPosition());

}

void Skeleton::Draw(sf::RenderWindow &window) {


    window.draw(sprite);
    window.draw(bounding_rect);
}