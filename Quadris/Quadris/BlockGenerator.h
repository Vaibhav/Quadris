#ifndef BLOCKGENERATOR_H
#define BLOCKGENERATOR_H

#include "BlockParser.h"
#include <vector>

class BlockGenerator {
public:
	virtual Block generateBlock() = 0;
protected:
	std::vector< Block > getParsedBlocks();
private:
	BlockParser blockParser;
};

#endif