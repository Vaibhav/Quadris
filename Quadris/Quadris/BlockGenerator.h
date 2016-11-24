#ifndef BLOCKGENERATOR_H
#define BLOCKGENERATOR_H

#include "BlockParser.h"


class BlockGenerator {
public: 
	virtual Block generateBlock() = 0;

private:
	BlockParser blockParser; 

};

#endif