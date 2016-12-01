#ifndef BLOCK_GENERATOR_BASE_H
#define BLOCK_GENERATOR_BASE_H

#include "BlockGenerator.h"
#include <vector>
#include <string>

//Will implement Level 0 funtionality
class BlockGeneratorBase : public BlockGenerator { 
public:
	
	BlockGeneratorBase(std::string);
	Block generateBlock() override;
private:
	std::string sequenceFile;
	std::vector<std::string> sequence;
	void parseSequence();
	int currentIndex;
	int numblocksInSequence;
	bool checkIfBlocksInSequenceExist(std::vector<Block>);
};








#endif