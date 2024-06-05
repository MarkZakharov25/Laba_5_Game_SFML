#include "Enemy.h"

Enemy::Enemy(const std::string& textureFile, const sf::Vector2i& size, int frames, int moveDistance, int health)
        : size(size), frames(frames), moveDistance(moveDistance), health(health),
          verticalSpeed(0), gravity(0.98f), onGround(false), X_index(0), Y_index(0),
          direction(1), distanceMoved(0), isAttacking(false), attackCooldown(0) {
    texture.loadFromFile(textureFile);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(X_index * 0, Y_index * 0, size.x, size.y));
    sprite.scale(7, 7);
}

void Enemy::Initialize() {
    bounding_rect.setFillColor(sf::Color::Transparent);
    bounding_rect.setOutlineColor(sf::Color::Green);
    bounding_rect.setOutlineThickness(2);
    font.loadFromFile("C:/Users/D/CLionProjects/Game_1/assets/fonts/Ultragonic.otf");
    healthText.setFont(font);
    healthText.setFillColor(sf::Color::White);
    healthText.setString(std::to_string(health));
}

void Enemy::Load() {
    X_index = 0;
    Y_index = 0;
    bounding_rect.setSize(sf::Vector2f(size.x * 7, size.y * 7));
}

void Enemy::Update(float& deltaTime, const std::vector<TileObject>& objects, float& frame, const sf::Vector2f& playerPosition, Player& player) {
    attackCooldown -= deltaTime;
    if (health > 0) {
        sf::Vector2f moveDirection(0, 0);
        float distanceToPlayer = std::abs(sprite.getPosition().x - playerPosition.x);

        if (distanceToPlayer < 100.0f) {
            isAttacking = true;
            Y_index = 0;
            frame += 0.015f * deltaTime;
            if (frame >= frames) {
                frame = 0;
            }

            if (playerPosition.x < sprite.getPosition().x) {
                sprite.setTextureRect(sf::IntRect(size.x * (int)frame + size.x, Y_index * size.y, -size.x, size.y));
            } else {
                sprite.setTextureRect(sf::IntRect(size.x * (int)frame, Y_index * size.y, size.x, size.y));
            }

            if (attackCooldown <= 0) {
                attackCooldown = 5000;
                std::cout << "Checking collision between enemy and player" << std::endl;
                if (Math::IsCollisionHappen(sprite.getGlobalBounds(), player.GetGlobalBounds())) {
                    player.HandleTrapCollision();
                }
            }
        } else if (distanceToPlayer < 300.0f) {
            isAttacking = false;
            direction = playerPosition.x < sprite.getPosition().x ? -1 : 1;
            moveDirection.x = direction * 0.5f * deltaTime;
            Y_index = 5;
            frame += 0.01f * deltaTime;
            if (frame >= frames) {
                frame = 0;
            }

            if (direction == 1) {
                sprite.setTextureRect(sf::IntRect(size.x * (int)frame, Y_index * size.y, size.x, size.y));
            } else {
                sprite.setTextureRect(sf::IntRect(size.x * ((int)frame + 1), Y_index * size.y, -size.x, size.y));
            }
        } else {
            isAttacking = false;
            moveDirection.x = direction * 0.25f * deltaTime;
            Y_index = 5;
            frame += 0.01f * deltaTime;
            if (frame >= frames) {
                frame = 0;
            }

            if (direction == 1) {
                sprite.setTextureRect(sf::IntRect(size.x * (int)frame, Y_index * size.y, size.x, size.y));
            } else {
                sprite.setTextureRect(sf::IntRect(size.x * ((int)frame + 1), Y_index * size.y, -size.x, size.y));
            }

            distanceMoved += abs(moveDirection.x);
            if (distanceMoved >= moveDistance) {
                direction = -direction;
                distanceMoved = 0;
            }
        }

        if (!onGround) {
            verticalSpeed += gravity;
            moveDirection.y += verticalSpeed;
        }

        onGround = false;

        Math::handleVerticalCollisions(sprite, moveDirection, objects, onGround, verticalSpeed);
        sprite.move(moveDirection);

        if (onGround) {
            verticalSpeed = 0;
        }

        bounding_rect.setPosition(sprite.getPosition());
        healthText.setPosition(sprite.getPosition() + sf::Vector2f(size.x * 5, 0));
    }
}

void Enemy::Draw(sf::RenderWindow &window) const {
    if (health > 0) {
        window.draw(sprite);
        window.draw(healthText);
    }
}

void Enemy::ChangeHealth(int hp) {
    health += hp;
    healthText.setString(std::to_string(health));
}