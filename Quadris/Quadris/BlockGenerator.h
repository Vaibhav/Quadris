#ifndef BLOCKGENERATOR_H
#define BLOCKGENERATOR_H

#include "BlockParser.h"
#include "Block.h"
#include <vector>


class BlockGenerator {
public:
	virtual Block generateBlock() = 0;
protected:
	BlockGenerator();
	std::vector< Block > getParsedBlocks();
private:
	BlockParser blockParser;
	//Check if the 7 default blocks exist in the parsed blocks
	std::vector<std::string> baseBlocks;
	bool checkBaseBlocksExist(std::vector<Block>); 
};

#endif