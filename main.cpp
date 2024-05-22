#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Skeleton.h"
#include "TileMap.h"
#include <iostream>

float frame = 0;

int main() {
    Player player;
    Skeleton skeleton;
    sf::Clock clock;

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Rep Game");
    window.setFramerateLimit(240);

    player.Initialize();
    skeleton.Initialize();

    player.Load();
    skeleton.Load();

    TileMap map;
    if (!map.load("C:/Users/D/CLionProjects/untitled3/demo_level.tmx", "C:/Users/D/CLionProjects/untitled3/Tilesetv3.png")) {
        return -1;
    }

    const auto& objects = map.getObjects();
    for (const auto& obj : objects) {
        std::cout << "Object: " << obj.name << " Position: (" << obj.x << ", " << obj.y << ") Size: (" << obj.width << ", " << obj.height << ")\n";
    }

    float windowHeight = static_cast<float>(window.getSize().y);
    sf::FloatRect mapBounds = map.getLocalBounds();

    float scale = windowHeight / mapBounds.height;
    std::cout<<"scale:" << scale << std::endl;
    map.setScale(scale, scale);

//    float offsetX = (window.getSize().x - mapBounds.width * scale) / 2;

//    map.setPosition(offsetX, 0);

    while (window.isOpen()) {
        float time = clock.getElapsedTime().asMicroseconds();
        sf::Time deltaTimer = clock.restart();
        float deltaTime = deltaTimer.asMilliseconds();

        time = time / 1500;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));

        skeleton.Update(deltaTime);
        player.Update(frame, time, skeleton, deltaTime, mousePosition, objects);

        window.clear(sf::Color::Black);

        window.draw(map);
        player.Draw(window);
        skeleton.Draw(window);

        window.display();
    }

    return 0;
}



