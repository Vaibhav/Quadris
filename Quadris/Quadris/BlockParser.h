#ifndef BLOCKPARSER_H
#define BLOCKPARSER_H

#include <fstream>
#include <string>
#include <vector>
#include <memory>

class Block;

class BlockParser {
public:
	BlockParser(std::string fileName = "blocks.txt");
	~BlockParser();
	std::vector< std::shared_ptr<Block> > parseBlocks();
	std::shared_ptr<Block> createBlock(std::string);

private:
	std::string fileName;  

};

#endif

