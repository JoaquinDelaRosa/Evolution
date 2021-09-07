#ifndef SPECIESMANAGER_H_INCLUDED
#define SPECIESMANAGER_H_INCLUDED

#include "bits/stdc++.h"

class SpeciesManager{
    private:
        SpeciesManager(){}

    public:
        SpeciesManager(SpeciesManager const&) = delete;
        void operator=(SpeciesManager const&) = delete;

        static SpeciesManager& instance(){
            static SpeciesManager instance;
            return instance;
        }

};

#endif // SPECIESMANAGER_H_INCLUDED
