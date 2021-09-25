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

        std::vector<Entity*> getTop(int t){
            std::vector<Entity*> result;
            for(int i = 0; i < t; i++){
                if (this->entities->empty())
                    break;
                result.push_back(this->top());
                this->entities->pop();
            }

            for(int i = 0; i < (int) result.size(); i++){
                this->entities->push(result[i]);
            }

            return result;
        }

        bool isEmpty(){
            return this->N == 0;
        }
};

#endif // SPECIES_H
