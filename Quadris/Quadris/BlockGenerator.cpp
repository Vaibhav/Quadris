#include "BlockGenerator.h"
#include "BlockParser.h"
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

std::vector<Block> BlockGenerator::getParsedBlocks()
{	
	return this->blockParser.parseBlocks();
}

BlockGenerator::BlockGenerator(){
	this->baseBlocks = 
	vector<string>{"BLOCK-I", "BLOCK-Z", "BLOCK-T", "BLOCK-S", "BLOCK-O", "BLOCK-J", "BLOCK-L"};
	blockParser = BlockParser{};
}
	
bool BlockGenerator::checkBaseBlocksExist(std::vector<Block> blocks){
int size = baseBlocks.size();
for(int i = 0; i != size ; ++i ){
	if(std::find(baseBlocks.begin(), baseBlocks.end(), blocks[i].getName()) == baseBlocks.end()){
		return false;
	}
}
	return true;
}