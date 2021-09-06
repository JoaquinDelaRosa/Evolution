#ifndef SENSOR_H
#define SENSOR_H

#include<SFML/Graphics.hpp>
#include<bits/stdc++.h>
#include<VectorMath.h>
#include<Resources/Food.h>

class Entity;
class Food;

class ResourceSensor
{
    protected:
        Entity* owner;
        Resource* closest = nullptr;
        float signal = -1;
    public:

        float radius = 100;

        ResourceSensor(Entity* owner){
            this->owner = owner;
        }

        virtual Resource* sense(){
            return NULL;
        }

        virtual float getSignal(){
            return signal;
        }

        virtual ~ResourceSensor(){
            // Virtual destructor for sensor
        }

        Resource* getClosest(){
            return this->closest;
        }

        virtual float distance(){
            if(this->closest == nullptr)
                return INT_MAX;
            return getDistance(this->owner->getPosition(), this->closest->position);
        }


};

#endif // SENSOR_H
