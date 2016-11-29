#ifndef BLOCK_DECORATOR_H
#define BLOCK_DECORATOR_H

#include "Block.h"

class BlockDecorator : public Block {
public:

	BlockDecorator(Block * component) : component{ component } {}

	virtual ~BlockDecorator();
private:
	Block * component;
};

#endif