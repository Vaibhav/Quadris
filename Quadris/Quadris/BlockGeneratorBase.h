#ifndef BLOCK_GENERATOR_BASE_H
#define BLOCK_GENERATOR_BASE_H

#include "BlockGenerator.h"
#include <vector>
#include <string>
#include <memory>

//Will implement Level 0 funtionality
class BlockGeneratorBase : public BlockGenerator { 
public:
	
	BlockGeneratorBase(std::string);
	std::shared_ptr<Block> generateBlock() override;
private:
	std::string sequenceFile;
	std::vector<std::string> sequence;
	void parseSequence();
	int numblocksInSequence;
	int currentIndex;
	bool checkIfBlocksInSequenceExist(std::vector<std::shared_ptr<Block>>);
};


#endif