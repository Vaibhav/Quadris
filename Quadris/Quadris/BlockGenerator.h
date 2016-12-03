#ifndef BLOCKGENERATOR_H
#define BLOCKGENERATOR_H

#include "BlockParser.h"
#include "Block.h"
#include <vector>


class BlockGenerator {
public:
	virtual Block generateBlock() = 0;	
	Block generateBlock(std::string);
	std::vector<std::string> getBaseBlockNames();
	std::vector<std::string> getAllBlockNames();
protected:
	std::vector< Block > getParsedBlocks();
	std::vector< Block > getParsedBlocksBase();
	BlockGenerator();
private:
	BlockParser blockParser;
	//Check if the 7 default blocks exist in the parsed blocks
	std::vector<std::string> baseBlocks;
	std::vector<std::string> allBlocks;
	bool checkBaseBlocksExist(std::vector<Block>); 
};

#endif