#ifndef WORLD_
#define WORLD_

#include "SFML/Graphics.hpp"
#include "bits/stdc++.h"
#include "Resources/ResourceManager.h"
#include "Resources/Food.h"
#include "Resources/Waste.h"

class Entity;
template<typename T>
class Grid;

class Resource;

class World
{
    private:
        std::vector<Entity*> *entities;
        std::vector<Entity*> *buffer;
        std::priority_queue<Entity, std::vector<Entity*> , Entity::Compare> *removed;

        int width = 1000;
        int height = 1000;
        int offsetx = width / 2;
        int offsety = height / 2;

        int generation = 0;
        World();

        void setupManagers(){
            managers.emplace("Food" , new ResourceManager(new Food()));
            managers.emplace("Waste" , new ResourceManager(new Waste()));
        }


    public:
        World(World const&) = delete;
        void operator=(World const&) = delete;

        static World& instance(){
            static World instance;
            return instance;
        }

        // Mutators
        void addEntity(Entity* entity);
        std::vector<Entity*> *getEntities();

        // Resource Managers
        std::map<std::string, ResourceManager*> managers;

        // Update and Draw
        void update(float time);
        void repopulate();
        void formNextGeneration();
        void draw(sf::RenderWindow& window);

        bool outOfBounds(float x, float y);

        void displayGenerationInfo();
};

#endif // WORLD_
