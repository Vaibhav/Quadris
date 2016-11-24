#ifndef BLOCKFACTORY_H
#define BLOCKFACTORY_H

#include "BlockGenerator.h"
#include "BlockParser.h"

class BlockFactory {
public:
	Block generateBlock(int level = 0);
	int setLevel(int newLevel);

private:
	BlockGenerator * generator; 
	int level;
};

#endif

