#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include <chrono>

#include "include/Entity.h"
#include "include/World.h"
#include "include/Resources/Food.h"
#include "include/Resources/Waste.h"
#include "include/VectorMath.h"

#include "Clock.h"
#include "Constants.h"
int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Evolution");
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(WIDTH, HEIGHT ));

    for(int i = 0; i < ENTITY_COUNT; i++){
        Entity* e = new Entity(Generator::instance().getRandomVector());
        World::instance().addEntity(e);
    }

    for(int i = 0; i < FOOD_COUNT; i++){
        World::instance().managers["Food"]->addResource();
        World::instance().managers["Waste"]->addResource();
    }


    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        std::chrono::steady_clock::time_point current = std::chrono::steady_clock::now();

        // This allows us to account for fractional parts of the second
        int seconds = std::chrono::duration_cast<std::chrono::seconds>(current - start).count();
        int nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(current - start).count();

        float delta = seconds + (float )nanoseconds / 1000000.0f;
        start = current;


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Space)
                    World::instance().formNextGeneration();
            }
        }

        World::instance().update(delta * SPEED);
        Clock::instance().tick(delta * SPEED);

        window.clear();
        window.setView(view);
        World::instance().draw(window);
        window.display();

        // std::cout<<World::instance().getEntities()->size()<<"\n";
    }

    return 0;
}
