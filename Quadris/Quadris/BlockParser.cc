#include "BlockParser.h"
#include "Block.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std; 

/*

open blocks.txt 
contains block names seperated by spaces
each block name will have a "blockname.txt"

readin size coordinates (4 cells)

A.txt example
0 0
0 1
1 0
1 1 

coordinates are row, col

Block(char dispChar, std::string colour, std::string name, std::vector < std::pair < int, int >> coords);

*/

BlockParser::BlockParser(string fileName): fileName{ fileName } {}

BlockParser::~BlockParser() {}


std::vector< Block > BlockParser::parseBlocks() {
/*
	this->inputFileStream{fileName};
	string temp; 

	vector<string> v;

	while (getline(this->inputFileStream, temp, ' ')) {
		temp += ".txt";
		v.emplace_back(temp);
	}
	
	// this->fileName;
	// this->inputFileStream;
*/
	return vector<Block>();

}
