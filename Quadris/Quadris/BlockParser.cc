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

	// file stream
	ifstream input{file};

	// name is file name without the .txt extension 
	string name = file.substr(0, file.size() - 4);
	name = "BLOCK-" + name; 
	
	string line;
	string color;
	char dispChar;
	pair<int, int> coordinates;
	vector< pair <int, int>> v; 

	// gets the number of coords to read in 
//	cout << input.badbit;
	getline(input, line);
	int numOfCoords;
	stringstream ss { line };
//	cout << line << endl;
	// stores first line as numOfCoords 
	// ensures numOfCoords is int 
	if (!(ss >> numOfCoords)) {
		cout << name << endl;
		throw out_of_range("Improper input file. Check if size is an integer.");
	}
	
	
	// read in coordinates and store in vector of pairs
	for(int n = 0; n < numOfCoords; n++) {
    	
    	// get row and col coords
    	getline(input, line);
    	istringstream iss(line);
    	int row, col;

    	if (!(iss >> row >> col)) {
    		throw out_of_range("Improper input file. Check if coordinates are integers.");
    	}

    	// store coords in a vector to pass through Block constructor
    	coordinates.first = row;
    	coordinates.second = col;
    	v.emplace_back(coordinates);

    }

    // get display character and color 
    getline(input, line);
    dispChar = line[0];
    getline(input, line);
    color = line;

    // make a block and return it 
	Block newBlock{dispChar, color, name, v};
	return newBlock;

}


std::vector<Block> BlockParser::parseBlocks() {
	// open the file which contains the blocks 
	ifstream inputFileStream{this->fileName};
	string temp; 

	// create a vector of strings which will 
	// contain the file names which define the block
	vector<string> listOfFiles;
	// stores the block after the creation 
	vector<Block> blocks;

	// reads file which contains the blocks the user has defined
	// splits at space
	while (getline(inputFileStream, temp, ' ')) {
		// append the file extension before storing to vector
		temp += ".txt";
		listOfFiles.emplace_back(temp);
	}
	
	// go though vector and create blocks from the definition in the text files 
	int lofsize = listOfFiles.size();
	for (int i = 0; i < lofsize-1; i++) {
		blocks.emplace_back(createBlock(listOfFiles[i]));
		vector<Cell> cells = blocks[i].getCells();
	} 

	return blocks;
}

// Example blocks.txt file

/* 
I J L O S Z T
*/ 

//Example I.txt 
/*
4
0 0
0 1
0 2
0 3
I
cyan
*/