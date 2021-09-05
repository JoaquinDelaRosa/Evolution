#ifndef RESOURCE_H_INCLUDED
#define RESOURCE_H_INCLUDED

#include "SFML/Graphics.hpp"
#include "Resources/ResourceTypes.h"

class Entity;

class Resource{
    protected:
        bool consumed = false;
        unsigned int id = ResourceTypes::NoneType;

    public:
        sf::Vector2f position = sf::Vector2f(0.0f, 0.0f);

        Resource(){

        }

        virtual ~Resource(){

        }

        virtual Resource* getCopy(){
            return new Resource();
        }

        Resource(sf::Vector2f position){
            this->position = position;
        }

        bool isConsumed(){
            return consumed;
        }

        virtual void consume(){

        }

        virtual void consume(Entity* e){

        }

        void activate(){
            this->consumed = false;
        }

        virtual void draw(sf::RenderWindow& window){

        }
        virtual void update(float time){

        }

        unsigned int getId(){
            return this->id;
        }
};


#endif // RESOURCE_H_INCLUDED
