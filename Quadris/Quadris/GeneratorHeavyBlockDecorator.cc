#include "GeneratorHeavyBlockDecorator.h"
#include <iostream>
#include <string>
#include <memory>
#include "HeavyBlockDecorator.h"

using namespace std;

GeneratorHeavyBlockDecorator::GeneratorHeavyBlockDecorator(
    shared_ptr<BlockGenerator> component,
    int height, shared_ptr<Board> board) 
: BlockGeneratorDecorator{component}, height{height}, board{board}{}



std::shared_ptr<Block> GeneratorHeavyBlockDecorator::generateBlock() {
    std::shared_ptr<Block> normalBlock  = component->generateBlock();
    std::shared_ptr<Block> heavyBlock = 
        std::shared_ptr<Block>{new HeavyBlockDecorator(normalBlock, height, board)};
    return heavyBlock;
}

std::shared_ptr<Block> GeneratorHeavyBlockDecorator::generateBlock(std::string blockName){
    std::shared_ptr<Block> normalBlock  = component->generateBlock(blockName);
    std::shared_ptr<Block> heavyBlock = 
        std::shared_ptr<Block>{new HeavyBlockDecorator(normalBlock, height, board)};
    return heavyBlock;
}

