#include "BlockFactory.h"
#include "Block.h"
#include "BlockGeneratorBase.h"
#include "GeneratorProbabilityDecorator.h"
#include <utility>
#include <memory>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

//class std::unique_ptr<T>

//BlockFactory::BlockFactory

Block BlockFactory::generateBlock(int level)
{
    
    Block generatedBlock;
    if (level == 0)
    {
	//auto p = make_unique<new BlockGeneratorBase{}>;
	unique_ptr<BlockGenerator> p{new BlockGeneratorBase{sequenceFile}};
	return p->generateBlock();
	//return Block();
    }
    else if (level == 1)
    {
        vector<double> probabilities = vector<double> 
        {1.0/12.0, 1.0/12.0, 1.0/6.0, 1.0/6.0, 1.0/6.0, 1.0/6.0, 1.0/6.0 };
       	vector<string> blocks =  
        vector<string>{"BLOCK-S", "BLOCK-Z", "BLOCK-T", "BLOCK-I", "BLOCK-O", "BLOCK-J", "BLOCK-L"};
      	shared_ptr<BlockGenerator> component {new BlockGeneratorBase{sequenceFile}};
        unique_ptr<BlockGenerator> p{new GeneratorProbabilityDecorator{
                                         component,
                                         blocks, 
                                         probabilities, 
                                         seed
                                         }}; 
        	generatedBlock = p->generateBlock(); 
    
    }
    else if (level == 2)
    {



    }
    else if (level == 3)
    {
    }
    else if (level == 4)
    {
    }
    generatedBlock.setLevel(level);
    return generatedBlock;
}

Block BlockFactory::generateBlock(string blockName)
{
	unique_ptr<BlockGenerator> p{new BlockGeneratorBase{sequenceFile}};
	return p->generateBlock(blockName);    
}

void BlockFactory::setSeed(int n)
{
    seed = n;
}

void BlockFactory::setSequenceFile(std::string sequenceFile)
{
    this->sequenceFile = sequenceFile;
}

void BlockFactory::noRandomBlock(std::string file)
{
    this->noRandom = true;
    this->noRandomBlockFile = file;
}

void BlockFactory::restoreRandom()
{
    this->noRandom = false;
    this->noRandomBlockFile = "";
}