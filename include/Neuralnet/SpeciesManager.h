#ifndef SPECIESMANAGER_H_INCLUDED
#define SPECIESMANAGER_H_INCLUDED

#include "bits/stdc++.h"
#include "Species.h"

class Entity;

class SpeciesManager{
    private:
        std::vector<Species*> *species;
        int id = 0;
        float similarityThreshold = 5.0f;

        SpeciesManager(){
            this->species = new std::vector<Species*>();
            this->id = 0;
            this->similarityThreshold = 5.0f;
        }

    public:
        SpeciesManager(SpeciesManager const&) = delete;
        void operator=(SpeciesManager const&) = delete;

        static SpeciesManager& instance(){
            static SpeciesManager instance;
            return instance;
        }

        void addSpecies(Entity* representative){
            Species* s = new Species(this->id);
            s->push(representative);
            this->species->push_back(s);
            this->id++;
        }

        void addEntity(Entity*  e);
        void repopulate();
        void displaySpeciesInfo();

        int getSpecies(Entity* e);

        int getMembersOfSpecies(int id);

        void update();

        float getSimilarityThreshold(){
            return this->similarityThreshold;
        }

};

#endif // SPECIESMANAGER_H_INCLUDED
