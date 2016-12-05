#ifndef BLOCKFACTORY_H
#define BLOCKFACTORY_H
#include "BlockGenerator.h"
#include "BlockParser.h"
#include <memory>

//#include "Level.h"
#include "Block.h"


class Board;

class BlockFactory {

public:
	BlockFactory(Board * board);
	std::shared_ptr<Block> generateBlock(int level);
	std::shared_ptr<Block> generateBlock(std::string blockName, int level);

	void setSeed(int n);
	void setSequenceFile(std::string sequenceFile);
	
	void setBoardHeight(int n);
	void setBoardWidth(int n);
	
	void noRandomBlock(std::string file);
	void restoreRandom();

private:
	std::unique_ptr<BlockGenerator> generator; // BlockGenerator is abstract, so need ptr
	int prevLevel;
	std::string sequenceFile;
	int seed;
	std::string noRandomBlockFile;
	bool noRandom;
	Board * board;
	int boardHeight;
	int boardWidth;

	std::unique_ptr<BlockGenerator> createBlockGenerator(int level);
	
};

#endif

