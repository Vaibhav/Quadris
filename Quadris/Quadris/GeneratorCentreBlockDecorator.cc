#include "GeneratorCentreBlockDecorator.h"
#include <iostream>
#include <string>
#include <memory>
//#include "CentreBlockDecorator.h"

using namespace std;

GeneratorCentreBlockDecorator::GeneratorCentreBlockDecorator(shared_ptr<BlockGenerator> component):
 BlockGeneratorDecorator{component}, numDropped{0}, rowCleared{false} {}



shared_ptr<Block> GeneratorCentreBlockDecorator::generateBlock() {
    shared_ptr<Block> normalBlock = component->generateBlock();
    if (numDropped % 5 == 0 && !rowCleared) {
    	//Block * centreBlock = new centreBlockDecorator();
    	vector<pair<int, int>> sqr{{0, 5}};
    	shared_ptr<Block> centreBlock{new Block{'*', "Brown", "Centre", sqr}};
    	return centreBlock;
	}
	numDropped++;
    return normalBlock;
}