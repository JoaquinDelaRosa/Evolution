#ifndef FOODDIGESTOR_H
#define FOODDIGESTOR_H

#include "SFML/Graphics.hpp"
#include "Resources/Resource.h"
#include "Resources/ResourceTypes.h"
#include "Resources/Waste.h"

class Entity;

class FoodDigester : public Component{
    // Abstract class for body components
    private:
        sf::CircleShape* body;
        Entity* entity;
        float radius = 5;

    public:
        FoodDigester(Entity* e){
            this->name = "FoodDigester";
            this->body = new sf::CircleShape(radius);
            this->body->setFillColor(sf::Color::Red);
            this->entity = e;
        }

        ~FoodDigester(){

        }

        virtual void draw(sf::RenderWindow& window){
            float angle = getAngle(this->entity->getDirection());
            this->body->setPosition(getVectorRadial(angle, 5, this->position ));
            window.draw(*this->body);
        }

        virtual void action(){

        }

        virtual void action(Resource* resource){
            if(resource->isConsumed())
                return;
            if(resource->getId() == ResourceTypes::FoodType){

                if(getDistance(resource->position, this->position) < 10.0f){
                    resource->consume(this->entity);
                    this->entity->health += 1.0f;
                    entity->target = nullptr;
                    World::instance().managers["Waste"]->addResource();
                }
            }
        }


        virtual void update(float time){
            entity->health -= time / 1000.0f;
        }
};

#endif // FOODDIGESTOR_H
