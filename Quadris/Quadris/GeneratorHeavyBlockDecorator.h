#ifndef GENERATOR_HEAVYBLOCK_DECORATOR
#define GENERATOR_HEAVYBLOCK_DECORATOR

#include "BlockGeneratorDecorator.h"
#include "Board.h"
#include <memory>
#include <vector>
#include <string>

class GeneratorHeavyBlockDecorator : public BlockGeneratorDecorator { 
public:
	GeneratorHeavyBlockDecorator(std::shared_ptr<BlockGenerator> component, int height, Board * board);
    std::shared_ptr<Block> generateBlock() override;

private:
    int height;
    Board * board;
};

#endif




