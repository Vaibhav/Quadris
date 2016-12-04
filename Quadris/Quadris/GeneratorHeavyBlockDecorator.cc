#include "GeneratorHeavyBlockDecorator.h"
#include <iostream>
#include <string>
#include <memory>
#include "HeavyBlockDecorator.h"

using namespace std;

GeneratorHeavyBlockDecorator::GeneratorHeavyBlockDecorator(shared_ptr<BlockGenerator> component) 
: BlockGeneratorDecorator{component}{}



Block GeneratorHeavyBlockDecorator::generateBlock() {
    Block normalBlock = component->generateBlock();
    Block * heavyBlock = new HeavyBlockDecorator(shared_ptr<Block>{&normalBlock});
    //return *(heavyBlock);
    return *heavyBlock;
}