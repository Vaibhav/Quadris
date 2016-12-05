#ifndef BLOCKGENERATOR_H
#define BLOCKGENERATOR_H

#include "BlockParser.h"
#include "Block.h"
#include <vector>
#include <memory>


class BlockGenerator {
public:
	virtual std::shared_ptr<Block> generateBlock() = 0;	
	virtual std::shared_ptr<Block> generateBlock(std::string);
	std::vector<std::string> getBaseBlockNames();
	std::vector<std::string> getAllBlockNames();
protected:
	std::vector< std::shared_ptr<Block> > getParsedBlocks();
	std::vector< std::shared_ptr<Block> > getParsedBlocksBase();
	BlockGenerator();
private:
	BlockParser blockParser;
	//Check if the 7 default blocks exist in the parsed blocks
	std::vector<std::string> baseBlocks;
	std::vector<std::string> allBlocks;
	bool checkBaseBlocksExist(std::vector<std::shared_ptr<Block>>); 
};

#endif

