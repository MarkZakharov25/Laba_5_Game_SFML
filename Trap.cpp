#include "Trap.h"


void Trap::Initialize(std::string fileName, sf::Vector2i size) {
    width = size.x;
    height = size.y;
    trapTexture.loadFromFile(fileName);
    trapSprite.setTexture(trapTexture);
    trapSprite.setTextureRect(sf::IntRect(0, 0, width, height));
    trapSprite.scale(8, 8);
    trapSprite.setPosition(sf::Vector2f(294.3, 700.210));
}


void Trap::Update(float &frame, float deltaTime, int frameCount) {
    frame += 0.01 * deltaTime;
    if(frame > frameCount){
        frame -= frameCount;
    }
    trapSprite.setTextureRect(sf::IntRect((width) * (int)frame, 0, width, height));

}

void Trap::Draw(sf::RenderWindow &window) {
    window.draw(trapSprite);
}

sf::Sprite Trap::getSprite() const{
    return trapSprite;
}

const sf::Vector2f& Trap::getPosition() const {
    return trapSprite.getPosition();
}
