#ifndef SENSOR_H
#define SENSOR_H

#include<SFML/Graphics.hpp>
#include<bits/stdc++.h>
#include<VectorMath.h>
#include<Resources/Food.h>

class Entity;
class Food;

class Sensor
{
    protected:
        Entity* owner;
        float signal = -1;

    public:

        float radius = 100;

        Sensor(Entity* owner){
            this->owner = owner;
        }

        virtual Resource* sense(){
            return NULL;
        }

        virtual Entity* senseEntity(){
            return NULL;
        }

        virtual float getSignal(){
            return signal;
        }

        virtual ~Sensor(){
            // Virtual destructor for sensor
        }

};

#endif // SENSOR_H
