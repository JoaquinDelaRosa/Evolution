#ifndef WASTESENSOR_H
#define WASTESENSOR_H

#include <Sensory/ResourceSensor.h>
#include <Resources/Waste.h>

class Entity;
class Resource;

class WasteSensor : public ResourceSensor{
    private:

    public:
        WasteSensor(Entity* entity) : ResourceSensor(entity){
            this->owner = entity;
            this->radius = 50.0f;
        };

        Resource* sense() override{
            Waste* closestWaste = nullptr;
            float distance = 1e6;
            this->signal = 0;
            sf::Vector2f position = owner->getPosition();

            std::vector<Resource*> wastes = *World::instance().managers["Waste"]->getResources();

            for(int i = 0; i < (int) wastes.size(); i++){
                if(wastes[i] == nullptr)
                    continue;

                double candidateDistance = getDistance(position, wastes[i]->position);

                if(candidateDistance < distance && candidateDistance <= radius){
                    distance = candidateDistance;
                    closestWaste = (Waste*) wastes[i];
                    this->signal ++;
                }
            }
            this->closest = closestWaste;

            return closestWaste;
        }

        float getSignal() override{
            return this->signal;
        }
};

#endif // WASTESENSOR_H
