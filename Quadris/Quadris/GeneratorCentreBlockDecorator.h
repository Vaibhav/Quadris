#ifndef GENERATOR_CENTRE_BLOCK_DECORATOR
#define GENERATOR_CENTRE_BLOCK_DECORATOR

#include "BlockGeneratorDecorator.h"
#include "Observer.h"

class GeneratorCentreBlockDecorator : public BlockGeneratorDecorator{//, Observer {
	int numDropped;
	bool rowCleared;
public:
	GeneratorCentreBlockDecorator(std::shared_ptr<BlockGenerator> component);
	std::shared_ptr<Block> generateBlock() override;



};

#endif
