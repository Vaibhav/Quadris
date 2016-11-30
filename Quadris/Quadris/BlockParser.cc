#include "BlockParser.h"
#include "Block.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std; 


BlockParser::BlockParser(string fileName): fileName{ fileName } {}

BlockParser::~BlockParser() {}


Block BlockParser::createBlock(string file){

	ifstream input{file};
	string line;
	string name = file.substr(0, file.size() - 4);
	string color;
	char dispChar;
	pair<int, int> coordinates;
	vector< pair <int, int>> v; 

	// gets the number of coords to read in 
	getline(input, line);
	int numOfCoords;

	stringstream ss { line };

	// stores first line as numOfCoords 
	// ensures numOfCoords is int 
	if (!(ss >> numOfCoords)) {
		throw out_of_range("Improper input file. Check if size is an integer.");
	}
	
	
	// read in coordinates and store in vector of pairs
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

	Block newBlock{dispChar, color, name, v};
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
