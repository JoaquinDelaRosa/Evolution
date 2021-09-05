#ifndef COMPONENT_H
#define COMPONENT_H

#include "SFML/Graphics.hpp"

class Entity;

class Component{
    // Abstract class for body components
    protected:
        Entity* owner;
    public:
        sf::Vector2f position;
        std::string name;

        Component(){

        }


        Component(Entity* owner){
            this->owner = owner;
        }

        ~Component(){

        }

        virtual void draw(sf::RenderWindow& window){

        }

        virtual void action(){
            // Perform some action
        }

        virtual void action(Resource* resource){
            // Perform an action with a resource
        }

        virtual void update(float time){
            // Update the body
        }
};


#endif // COMPONENT_H
