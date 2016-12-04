#include "GeneratorHeavyBlockDecorator.h"
#include <iostream>
#include <string>
#include <memory>
#include "HeavyBlockDecorator.h"

using namespace std;

GeneratorHeavyBlockDecorator::GeneratorHeavyBlockDecorator(shared_ptr<BlockGenerator> component) 
: BlockGeneratorDecorator{component}{}



std::shared_ptr<Block> GeneratorHeavyBlockDecorator::generateBlock() {
    std::shared_ptr<Block> normalBlock  = component->generateBlock();
    std::shared_ptr<Block> heavyBlock= 
    std::shared_ptr<Block>{new HeavyBlockDecorator(normalBlock)};
    //return *(heavyBlock);
    return heavyBlock;
}