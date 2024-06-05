#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Skeleton.h"
#include "TileMap.h"
#include "Trap.h"
#include "MapManager.h"
#include <iostream>
#include <vector>
#include "Energy.h"
#include "Enemy.h"

float frame_1 = 0;
float frame_2 = 0;
float frame_3 = 0;

int main() {
    Player player;
    Trap spike;
    sf::Clock clock;

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Rep Game");
    window.setFramerateLimit(240);

    sf::View camera(sf::FloatRect(0, 0, 1920, 1080));

    player.Initialize();
    spike.Initialize("C:/Users/D/CLionProjects/Game_1/assets/Trap/Spike_B.png", sf::Vector2i(32, 32));

    player.Load();
    std::vector<std::string> mapFiles = {
            "C:/Users/D/CLionProjects/untitled3/demo_level_4.tmx",
            "C:/Users/D/CLionProjects/untitled3/demo_level_5.tmx"
    };
    std::string tilesetFile = "C:/Users/D/CLionProjects/untitled3/Tilesetv3.png";

    MapManager mapManager(mapFiles, tilesetFile);
    TileMap& map = mapManager.getRandomMap();

    const auto& objects = map.getObjects();
    for (const auto& obj : objects) {
        std::cout << "Object: " << obj.name << " Position: (" << obj.x << ", " << obj.y << ") Size: (" << obj.width << ", " << obj.height << ")\n";
    }

    float windowHeight = static_cast<float>(window.getSize().y);
    sf::FloatRect mapBounds = map.getLocalBounds();

    float scale = windowHeight / mapBounds.height;
    std::cout << "scale:" << scale << std::endl;
    map.setScale(scale, scale);

    Enemy skeleton("C:/Users/D/CLionProjects/Game_1/assets/Enemies/Skeleton/textures/spritesheet.png", sf::Vector2i(22, 37), 18, 300, 50);
    skeleton.Initialize();
    skeleton.Load();

//    std::vector<Skeleton> skeletons;
//    std::vector<sf::Vector2f> spawnPositions = map.getSpawnPositions("Spawn_skeleton");
//    for (const auto& pos : spawnPositions) {
//        Skeleton skeleton;
//        skeleton.Initialize();
//        skeleton.Load();
//        skeleton.sprite.setPosition(pos);
//        skeletons.push_back(skeleton);
//    }

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

        sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window), camera);

//        for (auto& skeleton : skeletons) {
//            skeleton.Update(deltaTime, objects, frame_2, player.sprite.getPosition(), player);
//        }

        skeleton.Update(deltaTime, objects, frame_2, player.sprite.getPosition(), player);

        std::vector<Trap> traps = {spike};
        player.Update(frame_1, time, skeleton, deltaTime, mousePosition, objects, traps); // Пропускаємо першого скелета
        spike.Update(frame_3, deltaTime, 10);

        if (player.GetHealth() <= 0) {
            player.Respawn();
        }

        camera.setCenter(player.sprite.getPosition());
        window.setView(camera);

        window.clear(sf::Color::Black);

        window.draw(map);
        player.Draw(window);
//        for (const auto& skeleton : skeletons) {
//            skeleton.Draw(window);
//        }
        skeleton.Draw(window);
        spike.Draw(window);

        window.display();
    }

    return 0;
}
