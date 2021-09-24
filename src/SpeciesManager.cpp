#include "Neuralnet/SpeciesManager.h"
#include "Entity.h"
#include "Species.h"
#include "Constants.h"

void SpeciesManager::addEntity(Entity* e){
    if(e == nullptr)
        return;

    for(int i = 0; i < (int) this->species->size(); i++){
        Species* s = (*this->species)[i];
        if(s->top()->compatibleWith(e)){
            s->push(e);
            return;
        }
    }
    this->addSpecies(e);
}

void SpeciesManager::repopulate(){
    // Repopulate each species
    std::sort(this->species->begin(), this->species->end(), [](Species* a, Species* b) -> bool{
              if(a->top() == nullptr || b->top() == nullptr)
                return true;

              return a->top()->getFitness() > b->top()->getFitness();});
    int i;

    for(i = 0; i < std::min(SPECIES, (int) this->species->size()); i++){
        Species *s = (*this->species)[i];

        Entity* rep = s->top();         // Best performing entity of that species
        if(rep == nullptr){
            i--;
            delete s;
            continue;
        }

        for(int j = 0; j < (int) START_POP / SPECIES; j++)
            rep->reproduce();
        s->update();
    }


    for(int j = i; j < (int) this->species->size(); j++){
        Species* s = (*this->species)[j];
        this->species->erase(this->species->begin() + j);
        j--;
        delete s;
    }
}

void SpeciesManager::displaySpeciesInfo(){
    int width = 70;
    printTableCell("ID");
    printTableCell("Fitness");
    printTableCell("Lifetime");
    printTableCell("Children");
    printTableCell("Food Radius");
    printTableCell("Waste Radius");

    std::cout<<"\n";
    printHorizontal(width);

    for(int i = 0; i < (int) this->species->size(); i++){
        Species* s = (*this->species)[i];
        Entity* rep = s->top();
        rep->getStats();
        std::cout<<"\n";
    }

    printHorizontal(width);
}

int SpeciesManager::getSpecies(Entity* e){
    if(e == nullptr)
        return -1;

    for(int i = 0; i < (int) this->species->size(); i++){
        Species* s = (*this->species)[i];
        if(s->top()->compatibleWith(e)){
            return s->getId();
        }
    }
    int id = this->id;
    this->addSpecies(e);
    return id;
}

int SpeciesManager::getMembersOfSpecies(int id){
    for(int i = 0; i < (int) this->species->size(); i++){
        Species* s = (*this->species)[i];
        if(s->getId() == id)
            return s->getSize();
    }
    return 0;
}
