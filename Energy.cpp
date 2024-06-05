#include "Energy.h"
#include <iostream>

Energy::Energy(sf::Vector2f position) {
    shape.setSize(sf::Vector2f(20, 20));
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(position);
}

void Energy::Draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::FloatRect Energy::GetBounds() const {
    return shape.getGlobalBounds();
}
