#ifndef WASTESENSOR_H
#define WASTESENSOR_H

#include <Sensory/Sensor.h>
#include <Resources/Waste.h>

class Entity;
class Resource;

class WasteSensor : public Sensor{
    private:
        Waste* closest = nullptr;
    public:
        WasteSensor(Entity* entity) : Sensor(entity){
            this->owner = entity;
            this->radius = 50.0f;
        };

        Resource* sense() override{
            Waste* closestWaste = nullptr;
            float distance = 1e6;
            sf::Vector2f position = owner->getPosition();

            std::vector<Resource*> wastes = *World::instance().managers["Waste"]->getResources();

            for(int i = 0; i < (int) wastes.size(); i++){
                if(wastes[i] == nullptr)
                    continue;

                double candidateDistance = getDistance(position, wastes[i]->position);

                if(candidateDistance < distance && candidateDistance <= radius){
                    distance = candidateDistance;
                    closestWaste = (Waste*) wastes[i];
                }
            }

            this->signal = distance;
            if(closestWaste == nullptr){
                this->signal = MAX_PERCEPTION_RADIUS + 1;
            }
            closest = closestWaste;

            return closestWaste;
        }

        float getSignal() override{
            if(closest == nullptr)
                return -1;

            return getDistance(closest->position, this->owner->getPosition());
        }


};

#endif // WASTESENSOR_H
