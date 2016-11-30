#ifndef GENERATOR_PROBABILITY_DECORATOR
#define GENERATOR_PROBABILITY_DECORATOR

#include "BlockGeneratorDecorator.h"
#include <memory>
#include <vector>
#include <string>
class GeneratorProbabilityDecorator : BlockGeneratorDecorator{
public:
GeneratorProbabilityDecorator(std::shared_ptr<BlockGenerator> componenet);
GenerateProbabilityDecorator(std::shared_ptr<BlockGenerator> component,
std::vector<string> blocks, std::vector<double> probabilities);
Block generateBlock();

void setProbability(std::vector<std::string> blocks, std::vector<double> probabilities);

private:
std::vector<std::pair<std::string, double > > blockProbabilities;
};

#endif




