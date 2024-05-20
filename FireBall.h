#pragma once

#ifndef GAME_1_FIREBALL_H
#define GAME_1_FIREBALL_H

#include <SFML/Graphics.hpp>
#include "iostream"

class FireBall {

private:
    sf::Texture texture_fireball;
    sf::Sprite sprite_fireball;
    std::vector<sf::Sprite> container_of_fireball;

public:
    float speed;
    sf::Vector2i direction;
    float  fireRate;
public:
    void Initialize();
    void Load();
    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);

};


#endif //GAME_1_FIREBALL_H
