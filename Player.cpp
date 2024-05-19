#include "Player.h"
#include "Math.h"
#include "iostream"

void Player::Initialize() {

    bounding_rect.setFillColor(sf::Color::Transparent);
    bounding_rect.setOutlineColor(sf::Color::Red);
    bounding_rect.setOutlineThickness(2);


}

void Player::Load() {
    sprite.setPosition(150, 750);

    texture.loadFromFile("C:/Users/D/CLionProjects/Game_1/assets/main_character/textures/AnimationSheet_Character.png");

    sprite.setTexture(texture);
     X_index = 0;
     Y_index = 0;

    sprite.setTextureRect(sf::IntRect(X_index * size.x, Y_index * size.y, size.x, size.y));
    sprite.scale(5, 5);

    size = sf::Vector2i(32, 32);
    bounding_rect.setSize(sf::Vector2f(size.x * 5, size.y * 5));

    //---------------------------------------------------------------------------------------

    texture_fireball.loadFromFile("C:/Users/D/CLionProjects/Game_1/assets/main_character/textures/Firebolt_SpriteSheet.png");
    sprite_fireball.setTexture(texture_fireball);
    sprite_fireball.setTextureRect(sf::IntRect(0, 0, 50, 48 ));
    sprite_fireball.scale(3, 3);
}

void Player::Update(float& frame, float& time, Skeleton& skeleton) {

    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
        container_of_fireball.push_back(sprite_fireball);
        container_of_fireball[container_of_fireball.size() - 1].setPosition(sprite.getPosition());

    }

    for(int i = 0; i < container_of_fireball.size(); i++){
        sf::Vector2f direction = skeleton.sprite.getPosition() - container_of_fireball[i].getPosition();
        direction = Math::NormalizeVector(direction);
        container_of_fireball[i].setPosition(container_of_fireball[i].getPosition() + direction );
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        Y_index = 3;
        sprite.move(1 * time, 0);
        frame += 0.017 * time;
        if(frame > 8){
            frame -= 8;
        }
        sprite.setTextureRect(sf::IntRect((32) * (int)frame, Y_index * 32, 32, 32));
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        Y_index = 1;
        sprite.move(-1 * time, 0);
        frame += 0.015 * time;
        if(frame > 2){
            frame -= 2;
        }
        sprite.setTextureRect(sf::IntRect((32) * (int)frame, Y_index * 32, 32, 32));


    }


    else{
        Y_index = 0;
        frame += 0.003 * time;
        if(frame > 2){
            frame -= 2;
        }
        sprite.setTextureRect(sf::IntRect((32) * (int)frame, Y_index * 32, 32, 32));
    }

    bounding_rect.setPosition(sprite.getPosition());

    if(Math::IsCollisionHappen(sprite.getGlobalBounds(), skeleton.sprite.getGlobalBounds())){
        std::cout << "Collision" << std::endl;
    }

}

void Player::Draw(sf::RenderWindow& window){

    window.draw(sprite);
    window.draw(bounding_rect);
    for(int i = 0; i < container_of_fireball.size(); i++){
        window.draw(container_of_fireball[i]);
    }

}