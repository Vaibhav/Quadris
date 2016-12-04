#ifndef GENERATOR_HEAVYBLOCK_DECORATOR
#define GENERATOR_HEAVYBLOCK_DECORATOR

#include "BlockGeneratorDecorator.h"
#include <memory>
#include <vector>
#include <string>

class GeneratorHeavyBlockDecorator : public BlockGeneratorDecorator { 
public:
	GeneratorHeavyBlockDecorator(std::shared_ptr<BlockGenerator> component);
    Block generateBlock() override;
};

#endif




