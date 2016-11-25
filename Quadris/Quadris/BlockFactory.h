#ifndef BLOCKFACTORY_H
#define BLOCKFACTORY_H
#include "BlockGenerator.h"
#include "BlockParser.h"

//#include "Level.h"
#include "Block.h"

class BlockFactory {

public:
	Block generateBlock(int level = 0);
	int setLevel(int newLevel);
	
private:
	BlockGenerator *generator; // BlockGenerator is abstract, so need ptr
	int level; 

};

#endif

