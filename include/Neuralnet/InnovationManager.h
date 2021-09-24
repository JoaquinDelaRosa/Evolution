#ifndef INNOVATIONMANAGER_H_INCLUDED
#define INNOVATIONMANAGER_H_INCLUDED

#include "bits/stdc++.h"
#include "Neuralnet/NEATGene.h"


class InnovationManager{
    private:
        int ctr;
        std::vector<Gene*> genes;
        InnovationManager(){
            ctr = 0;
            genes = *(new std::vector<Gene*>());
        }

    public:
        InnovationManager(InnovationManager const&) = delete;
        void operator=(InnovationManager const&) = delete;

        static InnovationManager& instance(){
            static InnovationManager instance;
            return instance;
        }

        void update(){
            this->ctr++;
        }

        int get(){
            return this->ctr;
        }

        std::vector<Gene*> genome(){
            return this->genes;
        }

        void add(Gene* gene){
            this->genes.push_back(gene);
            gene->setInnovation(this->ctr);
            this->ctr++;
        }

        int has(Gene* gene){
            for(int i = 0 ; i < (int) this->genes.size(); i++){
                if(this->genes[i]->findex == gene->findex &&
                   this->genes[i]->flayer == gene->flayer &&
                   this->genes[i]->sindex == gene->sindex &&
                   this->genes[i]->slayer == gene->slayer)
                    return i;
            }
            return -1;
        }

};
inline void addGeneToManager(Gene* gene){
    int itr = InnovationManager::instance().has(gene);


    if(itr >= 0){
        gene->setInnovation(itr);
    }
    else{
        InnovationManager::instance().add(gene);
    }
}


#endif // INNOVATIONMANAGER_H_INCLUDED
