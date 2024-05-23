//
// Created by D on 19.05.2024.
//

#include "Math.h"
#include "cmath"

sf::Vector2f Math::NormalizeVector(sf::Vector2f vector){

    float m = sqrt(vector.x * vector.x + vector.y * vector.y) ;

    sf::Vector2f normalizedVector;

    normalizedVector.x = vector.x / m;
    normalizedVector.y = vector.y /m;

    return normalizedVector;
}

bool Math::IsCollisionHappen(sf::FloatRect rect1, sf::FloatRect rect2) {
    if(rect1.left + rect1.width >= rect2.left && rect2.left + rect1.width >= rect1.left
    && rect2.top + rect2.height >= rect1.top && rect1.top + rect1.height >=rect2.top){
        return true;
    }
    return false;
}

void Math::handleHorizontalCollisions(sf::Sprite& sprite, sf::Vector2f& moveDirection, const std::vector<TileObject>& objects) {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    bounds.left += moveDirection.x;

    for (const auto& object : objects) {
        if (object.name == "solid") {
            sf::FloatRect objectBounds(object.x, object.y, object.width, object.height);
            if (bounds.intersects(objectBounds)) {
                if (moveDirection.x > 0) {
                    moveDirection.x = objectBounds.left - bounds.left - bounds.width;
                } else if (moveDirection.x < 0) {
                    moveDirection.x = objectBounds.left + objectBounds.width - bounds.left;
                }
            }
        }
    }
}

void Math::handleVerticalCollisions(sf::Sprite& sprite, sf::Vector2f& moveDirection, const std::vector<TileObject>& objects, bool& onGround, float& verticalSpeed) {
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();
    spriteBounds.top += moveDirection.y;

    bool collisionDetected = false;

    for (const auto& object : objects) {
        if (object.name == "solid") {
            sf::FloatRect objectBounds(object.x, object.y, object.width, object.height);
            if (spriteBounds.intersects(objectBounds)) {
                if (moveDirection.y > 0) {
                    moveDirection.y = objectBounds.top - spriteBounds.top - spriteBounds.height;
                    onGround = true;
                } else if (moveDirection.y < 0) {
                    moveDirection.y = objectBounds.top + objectBounds.height - spriteBounds.top;
                }
                verticalSpeed = 0;
                collisionDetected = true;
            }
        }
    }

    if (!collisionDetected) {
        onGround = false;
    }
}


