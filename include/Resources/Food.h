#ifndef FOOD_H
#define FOOD_H

#include "Resource.h"
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "VectorMath.h"

class Food : public Resource
{
    private:
        sf::CircleShape* body;
    public:
        Food(sf::Vector2f position = sf::Vector2f(0.0f, 0.0f)) : Resource::Resource(){
            this->position = position;
            this->id = ResourceTypes::FoodType;
            this->value = 0.75f;

            this->body = new sf::CircleShape(3);
            this->body->setFillColor(sf::Color::Green);
            this->body->setPosition(position);
        }

        virtual ~Food(){

        }

        Resource* getCopy() override{
            return new Food(Generator::instance().getRandomVector());
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

#endif // FOOD_H
