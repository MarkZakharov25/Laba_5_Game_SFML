#include <iostream>
#include <SFML/Graphics.hpp>
#include "cmath"
#include "Player.h"
#include "Skeleton.h"


float frame = 0;

int main() {
    Player player;
    Skeleton skeleton;
    sf::Clock clock;

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Rep Game");

    player.Initialize();
    skeleton.Initialize();

    player.Load();
    skeleton.Load();





    while(window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();

        time = time / 1500;

        sf::Event event;
        while(window.pollEvent(event)){
             if(event.type == sf::Event::Closed){
                 window.close();
             }
        }

        skeleton.Update();
        player.Update(frame, time, skeleton);


        window.clear(sf::Color::Black);
        player.Draw(window);
        skeleton.Draw(window);

        window.display();
    }
    return 0;
}

