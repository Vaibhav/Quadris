#ifndef GENERATOR_CENTRE_BLOCK_DECORATOR
#define GENERATOR_CENTRE_BLOCK_DECORATOR

#include "BlockGeneratorDecorator.h"
#include "Observer.h"

//forward decl
class Board;

class GeneratorCentreBlockDecorator : public BlockGeneratorDecorator{//, Observer {
	int numDropped;
	bool rowCleared;
	Board *b;
public:
	GeneratorCentreBlockDecorator(std::shared_ptr<BlockGenerator> component, Board*b);
	std::shared_ptr<Block> generateBlock() override;



};

#endif
