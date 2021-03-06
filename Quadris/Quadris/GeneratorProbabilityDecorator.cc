#include "GeneratorProbabilityDecorator.h"
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdlib.h>

using namespace std;

GeneratorProbabilityDecorator::GeneratorProbabilityDecorator(
    std::shared_ptr<BlockGenerator> component,
    std::vector<string> blocks,
    int randSeed,
    int randomNumberRange)
    : BlockGeneratorDecorator{component},
      randSeed{randSeed},
      randomNumberRange{randomNumberRange}
{
     srand(randSeed);
     setEqualProbability(blocks);
}

GeneratorProbabilityDecorator::GeneratorProbabilityDecorator(
                               std::shared_ptr<BlockGenerator> component,
							   std::vector<string> blocks,
                               std::vector<double> probabilities,
                               int randSeed, int randomNumberRange)
                            :  BlockGeneratorDecorator{component},
                               randSeed{randSeed},
                               randomNumberRange{randomNumberRange}
{
    srand(randSeed);
    setProbability(blocks, probabilities);
}

std::shared_ptr<Block> GeneratorProbabilityDecorator::generateBlock()
{
    //Generate a number between 0 to 99 when randomNumberRange set to 100
    int num = (rand() % randomNumberRange);
    double totProb = 0;
    int size = blockProbabilities.size();
    for (int i = 0; i != size; ++i)
    {
	totProb += blockProbabilities[i].second;
	if (num < (totProb * randomNumberRange))
	{
        return this->component->generateBlock(blockProbabilities[i].first);
	}
    }
    return this->component->generateBlock(blockProbabilities[0].first);
}



void GeneratorProbabilityDecorator::setProbability(vector<string> blocks,
						                           vector<double> probabilities)
{

    int size = blocks.size();
    pair<string, double> item;

    if (blocks.size() != probabilities.size())
    {
	throw out_of_range("The list of blocks specified is not the same size as the list of probabilities specified");
    }

    for (int i = 0; i != size; ++i)
    {
	item.first = blocks[i];
	item.second = probabilities[i];
	this->blockProbabilities.emplace_back(item);
    }
}

void GeneratorProbabilityDecorator::setEqualProbability(std::vector<std::string> blocks){
    int size = blocks.size();
    double probability = static_cast<double>(1.0/size);
    vector<double> probabilities = vector<double>(size, probability);
    setProbability(blocks, probabilities);
}

