#include "Entity.h"
#include "VectorMath.h"
#include "World.h"

#include "Sensory/Brain.h"
#include "Sensory/FoodSensor.h"
#include "Sensory/WasteSensor.h"
#include "Sensory/EntitySensor.h"
#include "Sensory/Sensor.h"
#include "BodyComp/Body.h"

#include "Resources/Waste.h"

Entity::Entity(sf::Vector2f position)
{
    this->position = position;
    this->direction = normalize(Generator::instance().getRandomVector());

    this->speed = 0.5f;
    this->health = 50;
    this->isAlive = true;
    this->lifespan = 0;
    this->children = 0;

    this->brain = new Brain(this);
    this->body = new Body(this);

    this->initializeSensors();

    this->brain->encode();
}

Entity::~Entity(){
    delete this->brain;
}

void Entity::initializeSensors(){
    this->sensors = *(new std::map<std::string, Sensor*>());
    this->sensors.emplace("Food", new FoodSensor(this));
    this->sensors.emplace("Waste", new WasteSensor(this));

    this->entitySensor = new EntitySensor(this);

}

void Entity::draw(sf::RenderWindow& window){
    this->body->draw(window);

    // Draw a line to its target if any
    if(DEBUG){
        if(target != nullptr){
            sf::Vertex line[2] = {
                sf::Vertex(this->position),
                sf::Vertex(this->target->position)
            };

            window.draw(line, 2, sf::Lines);
        }
    }
}

void Entity::update(float time){
    this->health -= 0.005 * time;
    this->brain->think();

    this->position += this->speed * this->direction * time;


    if(health <= 0.0f){
        this->kill();
    }
    else{
        this->lifespan += time;
    }

    if(health >= 100.0f){
        this->reproduce();
        this->children++;
        this->health-=50;
    }

    this->updateDirection();
    // Update target
    if(target != nullptr){
        if(getDistance(target->position, this->position) > MAX_PERCEPTION_RADIUS){
            this->target = nullptr;
        }
    }

    this->body->update(time);
    this->body->act(target);
}

void Entity::updateDirection(){
    if(World::instance().outOfBounds(this->position.x, this->position.y)){
        this->direction = Generator::instance().getRandomVector();
        if(this->position.x <= -500){
            this->direction.x = Generator::instance().getRandomNumber(0, 500);
        }
        else if(this->position.x >= 500){
            this->direction.x = Generator::instance().getRandomNumber(-500, 0);
        }


        if(this->position.y <= -500){
            this->direction.y = Generator::instance().getRandomNumber(0, 500);
        }
        else if(this->position.y >= 500){
            this->direction.y = Generator::instance().getRandomNumber(-500, 0);
        }
    }
    this->direction = normalize(this->direction);
}

float Entity::getFitness(){
    return log(this->lifespan * (this->children + 1));
}

float Entity::distanceToTarget(){
    if(this->target == nullptr)
        return -1;

    return getDistance(this->target->position, this->position);
}

void Entity::reproduce(){
    Entity* e = new Entity(this->position);
    e->brain = new Brain(*this->brain, e);
    World::instance().addEntity(e);
}

void Entity::clone(){
    Entity* e = new Entity(this->position);
    e->brain = this->brain->clone(e);
    e->brain->encode();
    World::instance().addEntity(e);
}

void Entity::kill(){
    this->isAlive = false;
    World::instance().managers["Waste"]->addResource();
}

void Entity::search(std::string type){
    if(type == "Entity")
        this->otherEntity = this->entitySensor->senseEntity();
    else
        this->target = this->sensors[type]->sense();
}

void Entity::wander(){
    this->target = nullptr;
    this->otherEntity = nullptr;
}

void Entity::steerLeft(){
    rotateVector(&direction, PI / 30.0F);
}

void Entity::steerRight(){
    rotateVector(&direction, -PI / 30.0F);
}

void Entity::getStats(){
    printTableCell(this);
    printTableCell(this->getFitness());
    printTableCell(this->lifespan);
    printTableCell(this->children);
    printTableCell(this->brain->getGeneValue("FoodPerception"));
    printTableCell(this->brain->getGeneValue("WastePerception"));
    std::cout<<"\n";
}
