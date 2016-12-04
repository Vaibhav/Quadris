#include "BlockFactory.h"
#include "Block.h"
#include "BlockGeneratorBase.h"
#include "GeneratorProbabilityDecorator.h"
#include "GeneratorHeavyBlockDecorator.h"
#include "GeneratorCentreBlockDecorator.h"
#include <utility>
#include <memory>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

BlockFactory::BlockFactory(): prevLevel(-1) {
}

unique_ptr<BlockGenerator> BlockFactory::createBlockGenerator(int level){
    cerr << "called Create BlockGenerator" << endl;
    if (level == 0)
    {
    return unique_ptr<BlockGenerator>{new BlockGeneratorBase{sequenceFile}};
    }
    else if (level == 1)
    {
        vector<double> probabilities = 
            vector<double> {1.0/12.0, 1.0/12.0, 1.0/6.0, 1.0/6.0, 1.0/6.0, 1.0/6.0, 1.0/6.0 };
       	vector<string> blocks =  
            vector<string>{"BLOCK-S", "BLOCK-Z", "BLOCK-T", "BLOCK-I", "BLOCK-O", "BLOCK-J", "BLOCK-L"};
      	shared_ptr<BlockGenerator> component {new BlockGeneratorBase{sequenceFile}};
        return unique_ptr<BlockGenerator>{new GeneratorProbabilityDecorator{
                                         component,
                                         blocks, 
                                         probabilities, 
                                         seed
                                         }}; 
    }
    else if (level == 2)
    {
        	shared_ptr<BlockGenerator> component {new BlockGeneratorBase{sequenceFile}};
            return unique_ptr<BlockGenerator>{new GeneratorProbabilityDecorator{
                                         component,
                                         component->getAllBlockNames(),
                                         seed
                                         }};
    }
    else if (level == 3)
    {   
        vector<double> probabilities = 
            vector<double> {2.0/9.0, 2.0/9.0, 1.0/9.0, 1.0/9.0, 1.0/9.0, 1.0/9.0, 1.0/9.0 };
       	vector<string> blocks =  
            vector<string>{"BLOCK-S", "BLOCK-Z", "BLOCK-T", "BLOCK-I", "BLOCK-O", "BLOCK-J", "BLOCK-L"};
            
        shared_ptr<BlockGenerator> component {new BlockGeneratorBase{sequenceFile}};
        return unique_ptr<BlockGenerator>{ new GeneratorHeavyBlockDecorator{component}};
        /*return unique_ptr<BlockGenerator>{new GeneratorProbabilityDecorator{
                                         component,
                                         component->getAllBlockNames(),
                                         seed
                                         }};*/

    }
    else if (level == 4)
    {
    }
    //PLease delete THIS LINE
   return unique_ptr<BlockGenerator>{new BlockGeneratorBase{sequenceFile}};
}

Block BlockFactory::generateBlock(int level)
{
    //if prevLevel was == -1, then it Block factory has just been created
    if(prevLevel == -1 || prevLevel != level){
        
        //DBG
     //   cout << prevLevel << " fook " << level; 

        this->generator = createBlockGenerator(level);
        prevLevel = level;
    }
    Block generatedBlock = generator->generateBlock();
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