#include "Neuralnet/NeuralNetwork.h"
#include "Entity.h"
#include "BodyComp/Body.h"

void NeuralNetwork::getInputs(){
    inputs["EntityHealth"] = entity->getHealth();
    inputs["HasFoodDigester"] = entity->getBody()->hasComponent("FoodDigester");
    inputs["HasWasteDigester"] = entity->getBody()->hasComponent("WasteDigester");
    inputs["FoodSignal"] = entity->getResourceSensor("Food")->getSignal();
    inputs["WasteSignal"] = entity->getResourceSensor("Waste")->getSignal();
    inputs["NearestFood"] = entity->getResourceSensor("Food")->distance();
    inputs["NearestWaste"]= entity->getResourceSensor("Waste")->distance();
    inputs["Speed"] = entity->speed;

    inputs["TargetDistanceMemory"] = inputs["TargetDistance"];
    inputs["TargetDistance"] = entity->distanceToTarget();

    sf::Vector2f t = Generator::instance().getRandomVector();
    if(entity->target != nullptr)
        t = entity->target->position - entity->getPosition();

    inputs["AngleOffsetMemory"] = inputs["AngleOffset"];
    inputs["AngleOffset"] = getAngle(t) - getAngle(entity->getDirection());
    inputs["Constant"] = 1;

}

void NeuralNetwork::act(){
    if(outputs["Wander"] >= 0.5f){
            entity->wander();
        }
    if(outputs["SteerLeft"] >= 0.5f){
        entity->steerLeft();
    }
    if(outputs["SteerRight"]>= 0.5f){
        entity->steerRight();
    }
}
