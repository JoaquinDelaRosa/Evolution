#ifndef WASTE_H
#define WASTE_H

#include "Resource.h"
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "VectorMath.h"

class Waste : public Resource
{
    private:
        sf::CircleShape* body;
    public:
        Waste(sf::Vector2f position = sf::Vector2f(0.0f, 0.0f)) : Resource::Resource(){
            this->position = position;
            this->id = ResourceTypes::WasteType;
            this->value = 0.75f;

            this->body = new sf::CircleShape(3);
            this->body->setFillColor(sf::Color(128, 96, 77));
            this->body->setPosition(position);
        }

        virtual ~Waste(){

        }

        Resource* getCopy() override{
            return new Waste(Generator::instance().getRandomVector());
        }

        void consume() override{
            // Consume food;
            this->consumed = true;
        }

        void consume(Entity* e) override{
            this->consume();
        }

        void update(float time) override{
            this->body->setPosition(position);
        }

        void draw(sf::RenderWindow& window) override{
            if(!this->consumed)
                window.draw(*this->body);
        }
};

#endif // WASTE_H
