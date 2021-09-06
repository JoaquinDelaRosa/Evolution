#ifndef WASTEDIGESTOR_H
#define WASTEDIGESTOR_H

#include "SFML/Graphics.hpp"
#include "Resources/Resource.h"
#include "Resources/ResourceTypes.h"
#include "Sensory/ResourceSensor.h"

class Entity;

class WasteDigester : public Component{
    // Abstract class for body components
    private:
        sf::CircleShape* body;
        Entity* entity;
        float radius = 5;

    public:
        WasteDigester(Entity* e){
            this->name = "WasteDigester";

            this->body = new sf::CircleShape(radius);
            this->body->setFillColor(sf::Color::Yellow);
            this->entity = e;
        }

        ~WasteDigester(){

        }

        virtual void draw(sf::RenderWindow& window){
            float angle = getAngle(this->entity->getDirection());
            this->body->setPosition(getVectorRadial(angle, 5, this->position ));
            window.draw(*this->body);
        }

        virtual void action(){
            Resource* resource = entity->getResourceSensor("Waste")->getClosest();
            if(resource == nullptr)
                return;

            if(resource->isConsumed())
                return;

            if(resource->getId() == ResourceTypes::WasteType){;
                if(getDistance(resource->position, this->position) < 10.0f){
                    resource->consume(this->entity);
                    entity->health += resource->getValue();
                    entity->accumulatedHealth += resource->getValue();
                    entity->target = nullptr;
                }
            }
        }


        virtual void update(float time){
            // Update the body
            entity->health -= time / 1000.0f;
        }

};


#endif // WASTEDIGESTOR_H
