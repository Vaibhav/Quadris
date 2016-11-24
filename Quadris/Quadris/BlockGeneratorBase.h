#ifndef BLOCK_GENERATOR_BASE_H
#define BLOCK_GENERATOR_BASE_H

#include "BlockGenerator.h"
#include <vector>

class BlockGeneratorBase : BlockGenerator { //Will implement Level 0 funtionality
public:
	
	BlockGeneratorBase() {};
	Block generateBlock();
	

private:
	bool checkBaseBlocksExist(std::vector<Block>); //Check if the 6 default blocks exist in the parsed blocks
	std::vector< Block > lol;
	



};








#endif