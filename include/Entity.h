#ifndef ENTITY_H
#define ENTITY_H

#include "SFML/Graphics.hpp"
#include "Printer.h"
#include "bits/stdc++.h"

class FoodSensor;
class WasteSensor;
class EntitySensor;

class Resource;

class ResourceSensor;
class Body;
class Brain;

class Entity
{
    private:
        sf::Vector2f position;
        sf::Vector2f direction;

        bool isAlive;
        void initializeSensors();
        void updateDirection();

        float lifespan = 0;
        int children = 0;

        Body* body;
        Brain* brain;
        std::map<std::string, ResourceSensor*> sensors;             // resource sensors

    public:
        Entity(const& Entity) = delete;

        Resource* target = nullptr;
        Entity* otherEntity = nullptr;

        Entity(sf::Vector2f position);
        ~Entity();

        float speed;
        float health;
        float accumulatedHealth = 0;

        void draw(sf::RenderWindow& window);                      // Draw entity on screen
        void update(float time);                                  // Update the entity's position;


        void reproduce();
        void clone();

        bool alive(){ return isAlive;}
        void kill();

        void steerLeft();                                          // steering behavior
        void steerRight();                                         // steering behavior


        void searchResource(std::string type);                             // Find a resource of type type and set that as a target
        float distanceToTarget();
        void goToTarget();                                         // Go to the target resource selected, if any
        void goToEntity();                                         // Go to the other entit(ies) found, if any
        void wander();                                             // Forcefully set the target to none.

        void act();                                                // Perform action on target

        float getHealth() {return health;}
        sf::Vector2f getPosition(){ return this->position; }
        sf::Vector2f getDirection(){ return this->direction; }
        Body* getBody();
        Brain* getBrain();

        ResourceSensor* getResourceSensor(std::string key) { return this->sensors[key];}


        float getFitness();                                   // Calculate the fitness score of the entity.

        struct Compare{
            bool operator() (Entity*& lhs, Entity*& rhs){
                return lhs->getFitness() < rhs->getFitness();
            }
        };

        void getStats();

        void mutateBrain();
        bool compatibleWith(Entity* other);
};

#endif // ENTITY_H
