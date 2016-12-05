#ifndef BLOCKGENERATOR_DECORATOR_H
#define BLOCKGENERATOR_DECORATOR_H

#include "BlockGenerator.h"
#include <memory>

class BlockGeneratorDecorator : public BlockGenerator {
public:
	BlockGeneratorDecorator(std::shared_ptr< BlockGenerator > component) : component{component} {}
protected:
	std::shared_ptr< BlockGenerator > component;
};

#endif
