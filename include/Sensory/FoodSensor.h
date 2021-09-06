#ifndef FOODSENSOR_H
#define FOODSENSOR_H

#include <Sensory/ResourceSensor.h>

class Entity;

class FoodSensor : public ResourceSensor
{
    private:

    public:
        FoodSensor(Entity* entity) : ResourceSensor(entity){
            this->owner = entity;
            this->radius = 50.0f;
        };

        Resource* sense() override{
            Food* closestFood = nullptr;
            float distance = 1e6;
            this->signal = 0;

            sf::Vector2f position = owner->getPosition();

            std::vector<Resource*> foods = *World::instance().managers["Food"]->getResources();

            for(int i = 0; i < (int) foods.size(); i++){
                if(foods[i] == nullptr)
                    continue;

                double candidateDistance = getDistance(position, foods[i]->position);

                if(candidateDistance < distance && candidateDistance <= radius){
                    distance = candidateDistance;
                    closestFood = (Food*) foods[i];
                    this->signal++;
                }
            }
            this->closest = closestFood;
            return closestFood;
        }

        float getSignal() override{
            return this->signal;
        }
};

#endif // FOODSENSOR_H
