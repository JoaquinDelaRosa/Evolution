#ifndef ENTITYSENSOR_H
#define ENTITYSENSOR_H

#include <Sensory/ResourceSensor.h>

class Entity;

class EntitySensor : public ResourceSensor
{
    public:
        EntitySensor(Entity* entity) : ResourceSensor(entity){
            this->owner = entity;
            this->radius = 1000.0f;
        };
};

#endif // ENTITYSENSOR_H
