A simplified simulation of physical and cognitive evolution using a genetic algorithm. 

**How it Works**
The environment contains green and brown pellets (food and waste respectively). Both of these resoruces require specific body parts to be digested by entitites. Such features are encoded in the form genetically as the genotype of the Entity. 

Additionally, entities also have an instance of a Recurrent Neural Network, which simulates cognitive thought. Currently, this is evolved in the same way physical features are evolved. However, use of other algorithms such as NEAT are being explored.

The fitness function is proportional to how long an entity survives, and how much offspring it produces.
