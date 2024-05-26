#include "Shield.h"
#include "iostream"

Shield::Shield() : active(false), duration(3.0f), timer(0.0f) {
    shieldShape.setSize(sf::Vector2f(100, 100));
    shieldShape.setFillColor(sf::Color(0, 0, 255, 100));
}

void Shield::Activate() {
    if (!active) {
        active = true;
        timer = 0.0f;
        std::cout << "Shield activated" << std::endl;
    }
}

void Shield::Update(float deltaTime) {
    if (active) {
        timer += deltaTime;
        std::cout << "Shield timer: " << timer << std::endl;
        if (timer >= duration) {
            active = false;
            std::cout << "Shield deactivated" << std::endl;
        }
    }
}

void Shield::Draw(sf::RenderWindow& window, sf::Vector2f playerPosition) {
    if (active) {
        shieldShape.setPosition(playerPosition);
        window.draw(shieldShape);
    }
}

bool Shield::IsActive() const {
    return active;
}

bool Shield::TurnOffShield() {
    active = false;
    return active;
}
