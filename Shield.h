#pragma once

#ifndef GAME_1_SHIELD_H
#define GAME_1_SHIELD_H

#include "SFML/Graphics.hpp"

class Shield {
public:
    Shield();
    void Activate();
    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window, sf::Vector2f playerPosition);
    bool IsActive() const;
    bool TurnOffShield();

private:
    sf::RectangleShape shieldShape;
    bool active;
    float duration;
    float timer;
};


#endif //GAME_1_SHIELD_H
