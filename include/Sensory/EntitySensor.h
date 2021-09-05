#ifndef ENTITYSENSOR_H
#define ENTITYSENSOR_H

#include <Sensory/Sensor.h>

class Entity;

class EntitySensor : public Sensor
{
    public:
        EntitySensor(Entity* entity) : Sensor(entity){
            this->owner = entity;
            this->radius = 1000.0f;
        };

        Entity* senseEntity(){
            Entity* closestEntity = nullptr;
            float distance = 1e6;
            sf::Vector2f position = owner->getPosition();

            std::vector<Entity*> entities = *World::instance().getEntities();

            for(int i = 0; i < (int) entities.size(); i++){
                if(entities[i] == nullptr || entities[i] == this->owner)
                    continue;

                double candidateDistance = getDistance(position, entities[i]->getPosition());

                if(candidateDistance < distance && candidateDistance <= radius){
                    distance = candidateDistance;
                    closestEntity = entities[i];
                }
            }

            this->signal = distance;
            if(closestEntity == nullptr){
                this->signal = -1;
            }

            return closestEntity;
        }
};

#endif // ENTITYSENSOR_H
