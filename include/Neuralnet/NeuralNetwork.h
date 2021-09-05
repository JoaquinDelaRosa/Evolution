#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H
#include "bits/stdc++.h"
#include "VectorMath.h"

#include "Constants.h"

class Entity;

struct Neuron{
    float value;
    int index;
};

float sigmoid(float val){
    return 1.0f / (1.0f + exp(-val));
}

class NeuralNetwork{
    private:
        Entity* entity;
        int inputNeurons;
        int outputNeurons;
        const static int hiddenNeurons = 10;

        std::map<std::string, float> inputs;
        std::vector<float> hidden;
        std::map<std::string, float> outputs;

        std::vector<std::vector<float>> hiddenWeights;
        std::vector<std::vector<float>> outputWeights;

    public:
        NeuralNetwork(Entity* e){
            this->entity = e;
            initializeInputs();
            initializeHidden();
            initializeOutputs();
            this->inputNeurons = inputs.size();
            this->outputNeurons = outputs.size();
            initializeWeights();
        }

        NeuralNetwork(const NeuralNetwork& other, Entity* entity){
            if(this != &other){
                this->inputNeurons = other.inputNeurons;
                this->outputNeurons = other.outputNeurons;

                this->initializeInputs();
                this->initializeHidden();
                this->initializeOutputs();

                // Copy weights and mutate
                for(int i = 0; i < inputNeurons; i++){
                    std::vector<float> tmp;
                    for(int j = 0; j < hiddenNeurons; j++){
                        tmp.push_back(other.hiddenWeights[i][j]);
                    }
                    this->hiddenWeights.push_back(tmp);
                }


                for(int i = 0; i < hiddenNeurons; i++){
                    std::vector<float> tmp;
                    for(int j = 0; j < outputNeurons; j++){
                        tmp.push_back(other.outputWeights[i][j]);
                    }
                    this->outputWeights.push_back(tmp);
                }
                this->entity = entity;
            }
        }

        void initializeInputs(){
            this->inputs = *(new std::map<std::string, float>());
            this->inputs["AngleOffsetMemory"] = 0;
            this->inputs["TargetDistanceMemory"] = -1;
        }

        void initializeOutputs(){
            this->outputs = *(new std::map<std::string, float>());
            this->outputs["SearchFood"] = 0;
            this->outputs["SearchWaste"] = 0;
            this->outputs["Wander"] = 0;
            this->outputs["TurnLeft"] = 0;
            this->outputs["TurnRight"] = 0;
            this->outputs["SearchEntity"] = 0;
        }

        void initializeHidden(){
            this->hidden = *(new std::vector<float>());
            for(int i = 0; i < this->hiddenNeurons; i++){
                this->hidden.push_back(0);
            }
        }

        void initializeWeights(){
            for(int i = 0; i < inputNeurons; i++){
                std::vector<float> tmp;
                for(int j = 0; j < hiddenNeurons; j++){
                    float w = Generator::instance().getRandomNumber(-1.0f, 1.0f);
                    tmp.push_back(w);
                }
                this->hiddenWeights.push_back(tmp);

            }


            for(int i = 0; i < hiddenNeurons; i++){
                std::vector<float> tmp;
                for(int j = 0; j < outputNeurons; j++){
                    float w = Generator::instance().getRandomNumber(-1.0f, 1.0f);
                    tmp.push_back(w);
                }
                this->outputWeights.push_back(tmp);
            }
        }


        void mutate(){
            for(int i = 0; i < inputNeurons; i++){
                for(int j = 0; j < hiddenNeurons; j++){
                    float p = Generator::instance().getUniform();
                    // Mutate at a certain probability
                    if(p >= NEURAL_MUTATION_RATE)
                        continue;
                    hiddenWeights[i][j] += Generator::instance().getRandomNumber(-0.1f, 0.1f);
                    clamp<float>(-1.0f, 1.0f, &hiddenWeights[i][j]);
                }
            }


            for(int i = 0; i < hiddenNeurons; i++){
                for(int j = 0; j < outputNeurons; j++){
                    float p = Generator::instance().getUniform();
                    // Mutate at a certain probability
                    if(p >= NEURAL_MUTATION_RATE)
                        continue;
                    outputWeights[i][j] += Generator::instance().getRandomNumber(-0.1f, 0.1f);
                    clamp<float>(-1.0f, 1.0f, &outputWeights[i][j]);
                }
            }
        }

        void think(){
            getInputs();
            calculateHidden();
            calculateOutputs();
            act();
        }

        void getInputs(){
            inputs["EntityHealth"] = entity->getHealth();
            inputs["HasFoodDigester"] = entity->getBody()->hasComponent("FoodDigester");
            inputs["HasWasteDigester"] = entity->getBody()->hasComponent("WasteDigester");
//            inputs["FoodSignal"] = entity->getResourceSensor("Food")->getSignal();
//            inputs["WasteSignal"] = entity->getResourceSensor("Waste")->getSignal();
//            inputs["EntitySSignal"] = entity->getEntitySensor()->getSignal();


            inputs["TargetDistanceMemory"] = inputs["TargetDistance"];
            inputs["TargetDistance"] = entity->distanceToTarget();

            sf::Vector2f t = Generator::instance().getRandomVector();
            if(entity->target != nullptr)
                t = entity->target->position - entity->getPosition();

            inputs["AngleOffsetMemory"] = inputs["AngleOffset"];
            inputs["AngleOffset"] = getAngle(t) - getAngle(entity->getDirection());


        }

        void calculateHidden(){
            for(int i = 0; i < hiddenNeurons; i++){
                hidden[i] = 0.0f;
                int ctr = 0;
                for(auto j = inputs.begin(); j != inputs.end(); j++){
                    float input = j->second;
                    hidden[i] += input * hiddenWeights[ctr][i];
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

        void act(){
            if(outputs["SearchFood"] >= 0.5f){
                entity->search("Food");
            }
            if(outputs["SearchWaste"] >= 0.5f){
                entity->search("Waste");
            }
            if(outputs["Wander"] >= 0.5f){
                entity->wander();
            }
            if(outputs["TurnLeft"] >= 0.5f){
                entity->steerLeft();
            }
            if(outputs["TurnRight"] >= 0.5f){
                entity->steerRight();
            }
            if(outputs["SearchEntity"] >= 0.5f){
                entity->search("Entity");
            }
        }

        void display(){
            for(auto it = outputs.begin(); it != outputs.end(); it++){
                std::cout<<it->second<<"\n";
            }
            std::cout<<"----\n";
        }
};

#endif // NEURALNETWORK_H
