#pragma once

#ifndef GAME_1_TRAP_H
#define GAME_1_TRAP_H

#include "SFML/Graphics.hpp"


class Trap {
public:
    void Initialize(std::string fileName, sf::Vector2i size);
    void Update(float& frame, float deltaTime, int frameCount);
    void Draw(sf::RenderWindow& window);
    sf::Sprite getSprite() const;
    const sf::Vector2f& getPosition() const;

private:
    sf::Texture trapTexture;
    sf::Sprite trapSprite;
    int height;
    int width;


};



#endif //GAME_1_TRAP_H
