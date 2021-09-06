#ifndef RESOURCEMANAGER_H_INCLUDED
#define RESOURCEMANAGER_H_INCLUDED

#include "bits/stdc++.h"
#include "SFML/Graphics.hpp"
#include "Resources/Resource.h"
#include "VectorMath.h"

class ResourceManager{
    private:
        std::vector<Resource*> *resources;
        std::stack<Resource*> *pool;
        Resource* type;

    public:
        ResourceManager(Resource* type = nullptr){
            this->resources = new std::vector<Resource*>();
            this->pool = new std::stack<Resource*>();
            this->type = type;
        }

        void addResource(sf::Vector2f position = Generator::instance().getRandomVector()){
            if(type == nullptr)
                return;
            if(this->resources->size() >= 2000)
                return;

            Resource* resource = this->type->getCopy();
            if(this->pool->empty())
                resource = this->type->getCopy();
            else{
                resource = this->pool->top();
                this->pool->pop();
            }
            resource->position = position;
            resource->activate();
            this->resources->push_back(resource);

        }

        void addResource(int times){
            for(int i= 0 ; i < times; i++)
                this->addResource();
        }

        void update(float time){
            for(int i = 0; i < (int) this->resources->size(); i++){
                Resource* r = (*this->resources)[i];
                if(r != nullptr){
                    if(r->isConsumed()){
                        this->resources->erase(this->resources->begin() + i);
                        i--;
                        this->pool->push(r);
                    }
                    else
                        r->update(time);
                }
            }
        }

        void draw(sf::RenderWindow& window){
            for(int i = 0; i < (int) this->resources->size(); i++){
                if((*this->resources)[i] != nullptr)
                    (*this->resources)[i]->draw(window);
            }
        }

        std::vector<Resource*> *getResources(){
            return this->resources;
        }

};

#endif // RESOURCEMANAGER_H_INCLUDED
