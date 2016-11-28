#ifndef BLOCKFACTORY_H
#define BLOCKFACTORY_H
#include "BlockGenerator.h"
#include "BlockParser.h"

//#include "Level.h"
#include "Block.h"

class BlockFactory {

public:
	Block generateBlock(int level = 0);
	Block generateBlock(std::string blockName);

	void setSeed(int n);
	void setSequenceFile(std::string sequenceFile);
	
private:
	BlockGenerator *generator; // BlockGenerator is abstract, so need ptr
	
	std::string sequenceFile;
	int seed;
	std::string noRandomFile;
	bool enableRandom;
	
};

#endif

