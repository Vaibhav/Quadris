#ifndef BLOCK_DECORATOR_H
#define BLOCK_DECORATOR_H

#include "Block.h"

class BlockDecorator : public Block {
public:

	BlockDecorator(std::shared_ptr<Block> component) : component{ component } {}
	
protected:
	std::shared_ptr<Block> component;
};

#endif