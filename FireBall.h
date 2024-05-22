#pragma once

#ifndef GAME_1_FIREBALL_H
#define GAME_1_FIREBALL_H

#include <SFML/Graphics.hpp>
#include "iostream"

class FireBall {

private:
    sf::Texture texture_fireball;
    sf::Sprite sprite_fireball;
    sf::Vector2f direction;

public:
    float speed;

public:
    FireBall(std::string filename);
    void Initialize(const sf::Vector2f& position, sf::Vector2f& target, float speed);
    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);

    inline const sf::FloatRect GetGlobalBounds() {return sprite_fireball.getGlobalBounds();}

};


#endif //GAME_1_FIREBALL_H
