#ifndef BLOCKFACTORY_H
#define BLOCKFACTORY_H
#include "BlockGenerator.h"
#include "BlockParser.h"

//#include "Level.h"
#include "Block.h"

class BlockFactory {

public:
	Block generateBlock(int level = 0);
	
private:
	BlockGenerator *generator; // BlockGenerator is abstract, so need ptr
};

#endif

