#ifndef GENERATOR_PROBABILITY_DECORATOR
#define GENERATOR_PROBABILITY_DECORATOR

#include "BlockGeneratorDecorator.h"
#include <memory>
#include <vector>
#include <string>
class GeneratorProbabilityDecorator : public BlockGeneratorDecorator{
public:

    //Equal Probability Generation
    GeneratorProbabilityDecorator(std::shared_ptr<BlockGenerator> component,
                              std::vector<std::string> blocks,
                              int randSeed,
                              int randomNumberRange = 100);

    GeneratorProbabilityDecorator(std::shared_ptr<BlockGenerator> component,
                              std::vector<std::string> blocks,
                              std::vector<double> probabilities,
                              int randSeed,
                              int randomNumberRange = 100);

    Block generateBlock() override;

private:
    std::vector<std::pair<std::string, double > > blockProbabilities;
    int randSeed;
    const int randomNumberRange;


    void setProbability(std::vector<std::string> blocks, std::vector<double> probabilities);
    void setEqualProbability(std::vector<std::string> blocks);
};

#endif
