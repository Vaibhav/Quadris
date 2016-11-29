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

private:
	std::string fileName;  
//	std::ifstream inputFileStream;  VAIBHAV FCK IT DONT DO THIS SUCH A PAIN

};

#endif

