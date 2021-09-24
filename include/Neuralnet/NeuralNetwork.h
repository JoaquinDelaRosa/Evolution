#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H
#include "bits/stdc++.h"
#include "VectorMath.h"

#include "Constants.h"
#include "Neuralnet/InnovationManager.h"
#include "Neuralnet/NEATGene.h"

class Entity;

inline float sigmoid(float val){
    return 1.0f / (1.0f + exp(-val));
}



class NeuralNetwork{
    private:
        Entity* entity;
        int inputNeurons;
        int outputNeurons;
        int hiddenNeurons;

        std::map<std::string, float> inputs;
        std::vector<float> hidden;
        std::map<std::string, float> outputs;
        std::vector<Gene> genome;

        std::vector<std::vector<float>> hiddenWeights;
        std::vector<std::vector<float>> outputWeights;

    public:
        NeuralNetwork(Entity* e){
            this->entity = e;
            this->hiddenNeurons = 0;

            this->inputs = *(new std::map<std::string, float>());
            this->outputs = *(new std::map<std::string, float>());
            this->hidden = *(new std::vector<float>());
            this->genome = *(new std::vector<Gene>());

            initializeInputs();
            initializeOutputs();

            this->inputNeurons = inputs.size();
            this->outputNeurons = outputs.size();

            initializeWeights();
        }

        NeuralNetwork(const NeuralNetwork& other, Entity* entity){
            if(this != &other){
                this->inputNeurons = other.inputNeurons;
                this->outputNeurons = other.outputNeurons;
                this->hiddenNeurons = other.hiddenNeurons;
                this->genome = other.genome;

                this->inputs = other.inputs;
                this->outputs = other.outputs;
                this->hidden = other.hidden;

                this->hiddenWeights = other.hiddenWeights;
                this->outputWeights = other.outputWeights;
                this->entity = entity;
            }

        }

        void initializeInputs(){

            this->inputs["AngleOffsetMemory"] = 0;
            this->inputs["TargetDistanceMemory"] = -1;
            this->inputs["Constant"] = 1;

            inputs["EntityHealth"];
            inputs["HasFoodDigester"];
            inputs["HasWasteDigester"];
            inputs["FoodSignal"];
            inputs["WasteSignal"];
            inputs["NearestFood"];
            inputs["NearestWaste"];
            inputs["Speed"];
            inputs["TargetDistanceMemory"];
            inputs["TargetDistance"];
            inputs["AngleOffsetMemory"];
            inputs["AngleOffset"];

        }

        void initializeOutputs(){
            this->outputs["Wander"] = 0;
            this->outputs["TurnLeft"] = 0;
            this->outputs["TurnRight"] = 0;
            this->outputs["SearchEntity"] = 0;
        }

        void initializeWeights(){
            for(int i = 0; i < inputNeurons; i++){
                std::vector<float> tmp;
                for(int j = 0; j < hiddenNeurons; j++){
                    float w = 0;
                    tmp.push_back(w);
                }
                this->hiddenWeights.push_back(tmp);

            }


            for(int i = 0; i < hiddenNeurons; i++){
                std::vector<float> tmp;
                for(int j = 0; j < outputNeurons; j++){
                    float w = 0;
                    tmp.push_back(w);
                }
                this->outputWeights.push_back(tmp);
            }
        }


        void mutate(){
            // We follow the mutation algorithm in NEAT
            // We either add a connection, a node or modify existing connections
            int action = Generator::instance().getRandomInteger(1, 4);

            int i = Generator::instance().getRandomInteger(0, inputNeurons - 1);
            int o = Generator::instance().getRandomInteger(0, outputNeurons - 1) ;
            int h = Generator::instance().getRandomInteger(0, hiddenNeurons - 1);

            if(hiddenNeurons <= 0){
                addHidden();
                return;
            }

            switch(action){
            case 1:
                addHidden();
                break;
            case 2:
                if(this->hiddenWeights[i][h] == 0){
                    this->hiddenWeights[i][h] = Generator::instance().getRandomNumber(-1, 1);
                    this->addGene(0, i, 1, h, this->hiddenWeights[i][h]);
                }
                else{
                    this->hiddenWeights[i][h] += Generator::instance().getRandomNumber(-1, 1);
                }

                if(this->outputWeights[h][o] == 0){
                    this->outputWeights[h][o] = Generator::instance().getRandomNumber(-1, 1);
                    this->addGene(1, h, 2, o, this->outputWeights[h][o]);
                }
                else{
                    this->outputWeights[h][o] += Generator::instance().getRandomNumber(-1, 1);
                }

            case 3:
                this->hiddenWeights[i][h] += Generator::instance().getRandomNumber(-1, 1);
                break;

            case 4:
                this->outputWeights[h][o] += Generator::instance().getRandomNumber(-1, 1);
                break;
            }
        }

        void think(){
            getInputs();
            calculateHidden();
            calculateOutputs();
            act();
        }

        void getInputs();

        void calculateHidden(){
            for(int i = 0; i < hiddenNeurons; i++){
                hidden[i] = 0.0f;
                int ctr = 0;
                for(auto j = inputs.begin(); j != inputs.end(); j++){
                    float input = j->second;
                    hidden[i] += input * hiddenWeights[ctr][i];
                    ctr++;
                }
                hidden[i] = sigmoid(hidden[i]);
            }

        }

        void calculateOutputs(){
            int ctr = 0;
            for(auto it = outputs.begin(); it != outputs.end(); it++){
                it->second = 0.0f;
                for(int j = 0; j < hiddenNeurons; j++){
                    it->second += hidden[j] * outputWeights[j][ctr];
                }
                it->second = sigmoid(it->second);
                ctr++;
            }
        }

        void act();

        void display(){
            for(int i = 0; i < (int) this->genome.size(); i++){
                genome[i].display();
                std::cout<<"\n";
            }
        }

        void addHidden(){
            this->hidden.push_back(0);

            for(int i = 0; i < inputNeurons; i++){
                this->hiddenWeights[i].push_back(0);
            }

            std::vector<float> tmp;
            for(int j = 0; j < outputNeurons; j++){
                float w = 0;
                tmp.push_back(w);
            }
            this->outputWeights.push_back(tmp);

            this->hiddenNeurons++;
        }

        void addGene(int flayer, int findex, int slayer, int sindex, float weight){
            Gene* gene = new Gene(flayer, findex, slayer, sindex, weight);
            addGeneToManager(gene);
            this->genome.push_back(*gene);
        }

        float distance(NeuralNetwork* other){
            int excess = 0;
            int difference = 0 ;

            for(int i = 0; i < (int) this->genome.size(); i++){
                bool found = false;
                for(int o = 0; o < (int) other->genome.size(); o++){
                    if(this->genome[i].innovation == other->genome[o].innovation){
                        found = true;
                        break;
                    }
                }

                if(!found)
                    excess++;
            }

            for(int o = 0; o < (int) other->genome.size(); o++){
                bool found = false;
                for(int i = 0; i <  (int) this->genome.size(); i++){
                    if(this->genome[i].innovation == other->genome[o].innovation){
                        found = true;
                        break;
                    }
                }

                if(!found)
                    difference++;
            }

            return excess + difference;
        }
};

#endif // NEURALNETWORK_H
