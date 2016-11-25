#include "BlockGenerator.h"

std::vector<Block> BlockGenerator::getParsedBlocks()
{
	return this->blockParser.parseBlocks();
}
