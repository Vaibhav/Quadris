#include "GeneratorCentreBlockDecorator.h"
#include "Board.h"
#include <iostream>
#include <string>
#include <memory>
//#include "CentreBlockDecorator.h"

using namespace std;

GeneratorCentreBlockDecorator::GeneratorCentreBlockDecorator(
	shared_ptr<BlockGenerator> component, Board*b):
 BlockGeneratorDecorator{component}, numDropped{0}, b{b} {}



shared_ptr<Block> GeneratorCentreBlockDecorator::generateBlock() {
    shared_ptr<Block> normalBlock = component->generateBlock();
    if (b->wasRowCleared()) numDropped = 0;
    if (numDropped && numDropped % 5 == 0) {
    		b->addCentreBlock();
	}
	numDropped++;
    return normalBlock;
}