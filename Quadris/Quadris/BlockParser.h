#ifndef BLOCKPARSER_H
#define BLOCKPARSER_H

#include <fstream>
#include <string>
#include <vector>

class Block;

class BlockParser {
public:
	BlockParser();
	~BlockParser();
	std::vector< Block > parseBlocks();

private:
	std::string fileName = "blocks.txt";  
	std::ifstream inputFileStream; 

};

#endif

