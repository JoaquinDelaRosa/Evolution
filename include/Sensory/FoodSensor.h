#ifndef FOODSENSOR_H
#define FOODSENSOR_H

#include <Sensory/Sensor.h>

class Entity;

class FoodSensor : public Sensor
{
    private:
        Food* closest = nullptr;

    public:
        FoodSensor(Entity* entity) : Sensor(entity){
            this->owner = entity;
            this->radius = 50.0f;
        };

        Resource* sense() override{
            Food* closestFood = nullptr;
            float distance = 1e6;
            sf::Vector2f position = owner->getPosition();

            std::vector<Resource*> foods = *World::instance().managers["Food"]->getResources();

            for(int i = 0; i < (int) foods.size(); i++){
                if(foods[i] == nullptr)
                    continue;

                double candidateDistance = getDistance(position, foods[i]->position);

                if(candidateDistance < distance && candidateDistance <= radius){
                    distance = candidateDistance;
                    closestFood = (Food*) foods[i];
                }
            }

            this->signal = distance;
            if(closestFood == nullptr){
                this->signal = MAX_PERCEPTION_RADIUS + 1;
            }

            closest = closestFood;
            return (Food*) closestFood;
        }

        float getSignal() override{
            if(closest == nullptr)
                return -1;

            return getDistance(closest->position, this->owner->getPosition());
        }

};

#endif // FOODSENSOR_H
