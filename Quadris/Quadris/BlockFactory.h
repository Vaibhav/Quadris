#ifndef BLOCKFACTORY_H
#define BLOCKFACTORY_H
#include "BlockGenerator.h"
#include "BlockParser.h"
#include <memory>

//#include "Level.h"
#include "Block.h"

class BlockFactory {

public:
	BlockFactory();
	// We need this to be virtual so that it calls the correct function
	virtual std::shared_ptr<Block> generateBlock(int level = 0);
	std::shared_ptr<Block> generateBlock(std::string blockName);

	void setSeed(int n);
	void setSequenceFile(std::string sequenceFile);
	void noRandomBlock(std::string file);
	void restoreRandom();

private:
	std::unique_ptr<BlockGenerator> generator; // BlockGenerator is abstract, so need ptr
	int prevLevel;
	std::string sequenceFile;
	int seed;
	std::string noRandomBlockFile;
	bool noRandom;

	std::unique_ptr<BlockGenerator> createBlockGenerator(int level);
	
};

#endif

