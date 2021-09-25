#include "World.h"
#include<Entity.h>
#include<Resources/Food.h>
#include<Resources/Waste.h>
#include<Grid.h>
#include<Clock.h>

#include<VectorMath.h>
#include<Resources/ResourceManager.h>
#include<Neuralnet/SpeciesManager.h>
#include "Constants.h"
#include "Printer.h"

World::World()
{
    this->managers = *(new std::map<std::string, ResourceManager*>());
    setupManagers();

    this->entities = new std::vector<Entity*>();
    this->buffer = new std::vector<Entity*>();
}

void World::addEntity(Entity* entity){
    this->buffer->push_back(entity);
}


std::vector<Entity*> *World::getEntities(){
    return this->entities;
}

void World::update(float time){
    for(int i = 0; i < (int) this->buffer->size(); i++){
        Entity* entity = (*this->buffer)[i];
        this->entities->push_back(entity);
    }

    this->buffer->clear();

    for(int i = 0; i < (int) this->entities->size(); i++){
        Entity* entity = (*this->entities)[i];
        if(entity==nullptr){
            this->entities->erase(this->entities->begin() + i);
            i--;
            continue;
        }

        if(!entity->alive()){
            this->entities->erase(this->entities->begin() + i);
            i--;
            SpeciesManager::instance().addEntity(entity);
            continue;
        }

        if(entity != nullptr)
            entity->update(time);
    }


    if((int) Clock::instance().getTick() % TICKS_PER_PRUNE == 0 && (int) this->entities->size() >= MINIMUM_ENTITY_PRUNING_THRESHOLD){
        pruneWorst();
    }

    World::instance().managers["Food"]->update(time);
    World::instance().managers["Waste"]->update(time);

    if(this->entities->size() < 1){
        formNextGeneration();
    }
    repopulate();

}

void World::pruneWorst(){
    // Implementation of rtNEAT, we remove the entity with lowest adjusted fitness score.
    float worst = INT_MAX;
    Entity* worstEntity = nullptr;

    float best = 0;
    Entity* bestEntity = nullptr;

    for(int i = 0; i < (int) this->entities->size(); i++){
        Entity* entity = (*this->entities)[i];
        if(entity==nullptr){
            i--;
            continue;
        }

        int n = SpeciesManager::instance().getMembersOfSpecies(entity->getSpecies());
        if(n == 0)
            n = 1;

        int f = entity->getFitness() / n;               // adjusted fitness
        if(f < worst){
            worst = f;
            worstEntity = entity;
        }

        if(f >= best){
            best = f;
            bestEntity = entity;
        }
    }

    if(worstEntity != nullptr && worstEntity != bestEntity){
        worstEntity->kill();
        bestEntity->reproduce();
    }
}

void World::draw(sf::RenderWindow& window){
    for(int i = 0; i < (int) this->entities->size(); i++){
        if((*this->entities)[i] != nullptr)
            (*this->entities)[i]->draw(window);
    }

    this->managers["Food"]->draw(window);
    this->managers["Waste"]->draw(window);
}

void World::repopulate(){
    if(Clock::instance().ticked()){
        if(this->managers["Food"]->getResources()->size() <= MAX_FOOD)
            this->managers["Food"]->addResource(MAX_FOOD - this->managers["Food"]->getResources()->size());

        if(this->managers["Waste"]->getResources()->size() <= MAX_WASTE)
            this->managers["Waste"]->addResource(MAX_WASTE - this->managers["Waste"]->getResources()->size());
    }

}

void World::formNextGeneration(){
    for(int i = 0; i < (int) this->entities->size(); i++){
        SpeciesManager::instance().addEntity((*this->entities)[i]);
    }

    this->entities->clear();
    generation++;
    std::cout<<"Generation "<<generation<<"\n";

    SpeciesManager::instance().repopulate();
    SpeciesManager::instance().displaySpeciesInfo();
    SpeciesManager::instance().update();
}

bool World::outOfBounds(float x , float y){
    int left = -this->width / 2;
    int right = this->width / 2;
    int up = this->height / 2;
    int down = -this->height / 2;
    return ! (left <= x && x <= right && down  <= y && y <= up);
}
