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
