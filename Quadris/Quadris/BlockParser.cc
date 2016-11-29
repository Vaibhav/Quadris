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


Block createBlock(string file){

	ifstream input{file};
	string line;
	string name = file.substr(0, file.size() - 4);
	string color;
	char dispChar;
	pair<int, int> coordinates;
	vector< pair <int, int>> v; 

	//std::vector < std::pair < int, int >> coordinates;

	// gets the number of coords to read in 
	getline(input, line);
	int numOfCoords;

	stringstream ss { line };

	// stores first line as numOfCoords 
	ss >> numOfCoords; // error handling???
	
	for(int n = 0; n < numOfCoords; n++) {
    	
    	getline(input, line);
    	istringstream iss(line);
    	int row, col;

    	if (!(iss >> row >> col)) {
    		throw out_of_range("Improper input file. Check if coordinates are integers.");
    	}

    	coordinates.first = row;
    	coordinates.second = col;
    	v.emplace_back(coordinates);


    }

    getline(input, line);
    dispChar = line[0];
    getline(input, line);
    color = line;
    	
	Block newBlock = Block{dispChar, color, name, v};
	return newBlock;

}


std::vector<Block> BlockParser::parseBlocks() {

	ifstream inputFileStream{this->fileName};
	string temp; 

	vector<string> listOfFiles;
	vector<Block> blocks;

	while (getline(inputFileStream, temp, ' ')) {
		temp += ".txt";
		listOfFiles.emplace_back(temp);
	}
	
	for (int i = 0; i < listOfFiles.size(); i++) {
		blocks.emplace_back(createBlock(listOfFiles[i]));
	} 

	return blocks;

}
