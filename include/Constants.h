#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

// define all constants here

#define WIDTH 1000
#define HEIGHT 1000
#define ENTITY_COUNT 200
#define FOOD_COUNT 0
#define SPEED 1

#define SPECIES 6                          // Defines the number of top species to pick (including from previous generations).
#define GENERATION_SAMPLE_SIZE 3                  // Defines how many form the current generation per species will be sampled and allowed to move to the next next ggeneration
#define START_POP 200

#define NEURAL_MUTATION_RATE    0.99f
#define MAX_FOOD                300
#define MAX_WASTE               300
#define MAX_PERCEPTION_RADIUS   100.0f

#define MINIMUM_ENTITY_PRUNING_THRESHOLD 50         // Defines the minimum number of entities that need to be present before pruning can take place.
#define C1                      1.0f
#define C2                      1.0f

#define TICKS_PER_PRUNE         300
#define DEBUG 0
#endif // CONSTANTS_H_INCLUDED
