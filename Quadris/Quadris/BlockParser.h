#include <fstream>
#include <string>
#include <vector>

#include "Block.h"

class BlockParser {
public:
	BlockParser();
	std::vector< Block > parseBlocks();

private:
	std::string fileLocation; 
	std::ifstream inputFileStream; 


};