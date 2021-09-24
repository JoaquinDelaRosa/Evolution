#ifndef SPECIES_H
#define SPECIES_H

#include "bits/stdc++.h"
#include "Entity.h"

class Species
{
    private:
        std::priority_queue<Entity, std::vector<Entity*> , Entity::Compare>* entities;
        int N = 0;
        int id;

    public:
        Species(int id){
            this->id = id;
            this->N = 0;
            this->entities = new std::priority_queue<Entity, std::vector<Entity*> , Entity::Compare>();
        }

        void push(Entity* e){
            this->entities->emplace(e);
            this->N++;
        }

        Entity* top(){
            if(this->entities->empty())
                return nullptr;

            return this->entities->top();
        }

        void update(){
            // Delete all entities except the top entity
            Entity* top = this->top();
            this->entities->pop();

            delete entities;
            this->entities = new std::priority_queue<Entity, std::vector<Entity*> , Entity::Compare>();

            this->push(top);
            this->N = 1;
        }

        int getId(){
            return this->id;
        }

        int getSize(){
            return this->N;
        }
};

#endif // SPECIES_H
