#ifndef GENERATOR_PROBABILITY_DECORATOR
#define GENERATOR_PROBABILITY_DECORATOR

#include "BlockGeneratorDecorator.h"
#include <memory>
#include <vector>
#include <string>
class GeneratorProbabilityDecorator : public BlockGeneratorDecorator{
public:
GeneratorProbabilityDecorator(std::shared_ptr<BlockGenerator> , int, int randomNumberRange = 100);
GeneratorProbabilityDecorator(std::shared_ptr<BlockGenerator> , 
                             std::vector<std::string> , 
                             std::vector<double>, int, int randomNumberRange = 100);
                            



Block generateBlock() override;

void setProbability(std::vector<std::string> blocks, std::vector<double> probabilities);

private:
std::vector<std::pair<std::string, double > > blockProbabilities;
int randSeed;
const int randomNumberRange;
};

#endif




