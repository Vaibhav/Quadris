#ifndef GENERATOR_PROBABILITY_DECORATOR
#define GENERATOR_PROBABILITY_DECORATOR

#include "BlockGeneratorDecorator.h"
#include <memory>

class GeneratorProbabilityDecorator : BlockGeneratorDecorator{

GeneratorProbabilityDecorator(std::shared_ptr<BlockGenerator> componenet);

Block generateBlock();

};

#endif




