#include "World.h"
#include<Entity.h>
#include<Resources/Food.h>
#include<Resources/Waste.h>
#include<Grid.h>
#include<Clock.h>

#include<VectorMath.h>
#include<Resources/ResourceManager.h>
#include "Constants.h"
#include "Printer.h"

World::World()
{
    this->managers = *(new std::map<std::string, ResourceManager*>());
    setupManagers();

    this->entities = new std::vector<Entity*>();
    this->buffer = new std::vector<Entity*>();
    this->removed = new std::priority_queue<Entity, std::vector<Entity*> , Entity::Compare>();
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
            // If this is the last entity alive, we simply repopulate the simulation with clones of this entity.
            // Since it is the last one alive, it is also, most likely, the best
            this->entities->erase(this->entities->begin() + i);
            i--;
            this->removed->push(entity);
            continue;
        }

        if(entity != nullptr)
            entity->update(time);
    }

    World::instance().managers["Food"]->update(time);
    World::instance().managers["Waste"]->update(time);

    if(this->entities->size() < 1){
        formNextGeneration();
    }
    repopulate();

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
        this->removed->push((*this->entities)[i]);
    }

    this->entities->clear();
    generation++;
    displayGenerationInfo();

    std::vector<Entity*> tmp;

    for(int i = 0; i < EXTINCT_SIZE && !this->removed->empty(); i++){
        Entity* entity = this->removed->top();

        this->removed->pop();
        for(int j = 0; j < START_POP / (EXTINCT_SIZE - i + 1); j++){
            entity->reproduce();
        }
        entity->clone();
        tmp.push_back(entity);
    }

    while(!this->removed->empty()){
        Entity* e = this->removed->top();
        this->removed->pop();
        delete e;
    }

    for(int i = 0; i < (int) tmp.size(); i++){
        removed->push(tmp[i]);
    }
}

bool World::outOfBounds(float x , float y){
    int left = -this->width / 2;
    int right = this->width / 2;
    int up = this->height / 2;
    int down = -this->height / 2;
    return ! (left <= x && x <= right && down  <= y && y <= up);
}

void World::displayGenerationInfo(){
    int width = 70;
    std::cout<<"Generation "<<generation<<"\n";
    printTableCell("ID");
    printTableCell("Fitness");
    printTableCell("Lifetime");
    printTableCell("Children");
    printTableCell("Food Radius");
    printTableCell("Waste Radius");

    std::cout<<"\n";
    printHorizontal(width);

    std::vector<Entity*> tmp;

    for(int i = 0; i < EXTINCT_SIZE && !this->removed->empty(); i++){
        Entity* entity = this->removed->top();
        entity->getStats();

        this->removed->pop();
        tmp.push_back(entity);
    }

    for(int i = 0; i < (int) tmp.size(); i++){
        removed->push(tmp[i]);
    }

    printHorizontal(width);
}
