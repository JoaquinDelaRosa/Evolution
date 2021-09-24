#ifndef BRAIN_H
#define BRAIN_H

#include<bits/stdc++.h>
#include<VectorMath.h>
#include<BodyComp/Body.h>
#include<Sensory/EntitySensor.h>
#include<Allele.h>
#include "Neuralnet/NeuralNetwork.h"

#include "Constants.h"

class Entity;

class Brain
{
    std::map<std::string, Allele<float>*> gene;
    Entity* entity;
    NeuralNetwork* nn;

    public:
        Brain(Entity* entity , bool mutate = false){
            this->gene = *new std::map<std::string, Allele<float>*>();
            this->entity = entity;
            this->nn = new NeuralNetwork(entity);

            addAllele(new Allele<float>("FoodProbability", 0, 1, Generator::instance().getUniform()));
            addAllele(new Allele<float>("WasteProbability", 0, 1, Generator::instance().getUniform()));

            addAllele(new Allele<float>("FoodDigester", -1, 1, Generator::instance().getRandomNumber(-1.0f, 1.0f)));
            addAllele(new Allele<float>("WasteDigester", -1, 1, Generator::instance().getRandomNumber(-1.0f, 1.0f)));

            addAllele(new Allele<float>("FoodPerception", 0, 100, Generator::instance().getRandomNumber(10.0f, MAX_PERCEPTION_RADIUS)));
            addAllele(new Allele<float>("WastePerception", 0, 100, Generator::instance().getRandomNumber(10.0f, MAX_PERCEPTION_RADIUS)));
            addAllele(new Allele<float>("EntityPerception", 0, 100, Generator::instance().getRandomNumber(10.0f, MAX_PERCEPTION_RADIUS)));


            addAllele(new Allele<float>("EntitySpeed", 0.0f, 1.0f, Generator::instance().getRandomNumber(0.0f, 1.0f), 0.1f));

        }

        Brain(const Brain& other, Entity* entity){
            if(this!= &other && this->entity != entity){
                this->gene = *(new std::map<std::string, Allele<float>*>());
                for(auto it  = other.gene.begin(); it!= other.gene.end(); it++){
                    this->addAllele(new Allele<float>(it->first, it->second->getMin(), it->second->getMax(), it->second->getValue()));

                }
                this->entity = entity;

                this->nn = new NeuralNetwork(*other.nn, entity);
                this->mutate();
                this->encode();
            }

        }

        Brain* clone(Entity* entity){
            Brain* b = new Brain(entity);
            b->gene = this->gene;
            b->nn = new NeuralNetwork(*this->nn, entity);
            return b;
        }

        void addAllele(Allele<float>* a){
            this->gene.emplace(a->getName(), a);
        }

        void mutate(){
            // Mutate the brain's gene.
            for(auto it = this->gene.begin(); it != this->gene.end(); it++){
                it->second->mutate();
            }
            this->nn->mutate();
        }

        void encode(){
            // Encode gene characteristics as phenotype
            Body* body = entity->getBody();
            if(body == nullptr)
                return;

            if(this->gene["FoodDigester"]->getValue() > 0)
                body->addComponent(new FoodDigester(entity));
            if(this->gene["WasteDigester"]->getValue() > 0)
                body->addComponent(new WasteDigester(entity));

            //this->entity->getEntitySensor()->radius = gene["EntityPerception"]->getValue();
            this->entity->getResourceSensor("Food")->radius = gene["FoodPerception"]->getValue();
            this->entity->getResourceSensor("Waste")->radius = gene["WastePerception"]->getValue();

            this->entity->speed = this->gene["EntitySpeed"]->getValue();

        }


        void think(){
            nn->think();
        }

        float getGeneValue(std::string name){
            return gene[name]->getValue();
        }

        void display(){
            this->nn->display();
        }

        void mutateNN(){
            this->nn->mutate();
        }

        bool getCompatibility(Brain* other){
            if(other == nullptr)
                return false;

            float q = C1 * this->distance(other) + C2 * this->nn->distance(other->nn);

            if(q <= THRESHOLD)
                return true;
            return false;
        }

        float distance(Brain* other){
            float tot = 0;
            auto it = this->gene.begin();
            auto ot = other->gene.begin();

            while(it != this->gene.end() && ot != this->gene.end()){
                float dx = it->second->getWeight() - ot->second->getWeight();
                tot += dx * dx;
                it++;
                ot++;
            }

            return sqrt(tot);
        }
};

#endif // BRAIN_H
