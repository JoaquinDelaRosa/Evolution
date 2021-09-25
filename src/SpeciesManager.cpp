#include "Neuralnet/SpeciesManager.h"
#include "Entity.h"
#include "Species.h"
#include "Constants.h"

void SpeciesManager::addEntity(Entity* e){
    if(e == nullptr)
        return;

    for(int i = 0; i < (int) this->species->size(); i++){
        Species* s = (*this->species)[i];
        if(s->top()->compatibleWith(e, this->similarityThreshold)){
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
              if(a->getSize() == 0)
                return true;
              if(b->getSize() == 0)
                return true;

              return a->top()->getFitness() / a->getSize() > b->top()->getFitness() / b->getSize();});
    int i;

    for(i = 0; i < std::min(SPECIES, (int) this->species->size()); i++){
        Species *s = (*this->species)[i];
        if(s->isEmpty()){
            i--;
            delete s;
            continue;
        }

        std::vector<Entity*> sample = s->getTop(GENERATION_SAMPLE_SIZE);

        for(int k = 0; k < (int) sample.size(); k++){
            for(int j = 0; j < (int) START_POP / (SPECIES * (int) sample.size()) - 1; j++){
                sample[k]->reproduce();
            }
            sample[k]->clone();
        }
    }

    for(int j = i; j < (int) this->species->size(); j++){
        Species* s = (*this->species)[j];
        this->species->erase(this->species->begin() + j);
        j--;
        delete s;
    }
}

void SpeciesManager::update(){
    int i;

    for(i = 0; i < std::min(SPECIES, (int) this->species->size()); i++){
        Species *s = (*this->species)[i];
        if(s->isEmpty()){
            i--;
            delete s;
            continue;
        }
        s->update();
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
        std::cout<<"\nCount = "<<s->getSize()<<"\n\n";
    }

    printHorizontal(width);
}

int SpeciesManager::getSpecies(Entity* e){
    if(e == nullptr)
        return -1;

    for(int i = 0; i < (int) this->species->size(); i++){
        Species* s = (*this->species)[i];
        if(s->top()->compatibleWith(e, this->similarityThreshold)){
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
