#ifndef BLOCKPARSER_H
#define BLOCKPARSER_H

#include <fstream>
#include <string>
#include <vector>

class Block;

class BlockParser {
public:
	BlockParser(std::string fileName = "blocks.txt");
	~BlockParser();
	std::vector< Block > parseBlocks();
	Block createBlock(std::string);

private:
	std::string fileName;  

};

#endif

