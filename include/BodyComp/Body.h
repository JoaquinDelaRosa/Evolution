#ifndef BODY_H
#define BODY_H

#include<SFML/Graphics.hpp>
#include<bits/stdc++.h>

#include "BodyComp/Component.h"
#include "BodyComp/WasteDigester.h"
#include "BodyComp/FoodDigester.h"

class Component;
class Entity;
class Resource;

class Body{
    // Class describes the entity's body and also its components.
    private:
        std::vector<std::string> names;
        std::vector<Component*> components;
        sf::CircleShape* mainbody;
        Entity* owner;

        float radius = 5;

    public:
        Body(Entity* e){
            mainbody = new sf::CircleShape(radius);
            this->components = *(new std::vector<Component*>());
            owner = e;
        }

        void act(){

            for(int i = 0; i < (int) components.size(); i++){
                components[i]->action();
            }
        }

        void draw(sf::RenderWindow& window){
            window.draw(*mainbody);
            for(int i = 0; i < (int) components.size(); i++){
                components[i]->position = mainbody->getPosition() + sf::Vector2f(radius /2 , radius /2 );
                components[i]->draw(window);
            }
        }

        void update(float time){
            mainbody->setPosition(owner->getPosition());
            for(int i = 0; i < (int) components.size(); i++){
                components[i]->update(time);
            }
        }

        void addComponent(Component* component){
            this->names.push_back(component->name);
            this->components.push_back(component);
        }

        int hasComponent(std::string name){
            int ctr = 0;
            for(int i = 0; i < (int) this->names.size(); i++){
                if(this->names[i] == name)
                    ctr++;
            }
            return ctr;
        }

};

#endif // BODY_H
