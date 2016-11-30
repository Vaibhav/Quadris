#include "BlockGeneratorBase.h"
#include <string>   
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

BlockGeneratorBase::BlockGeneratorBase(string file): sequenceFile{file} {
	this->sequence = vector<string>{};
	parseSequence();
	this->currentIndex = 0;
	this->numblocksInSequence = this->sequence.size();

	/*for(int i = 0; i!= numblocksInSequence; ++i){
		cout << this->sequence[i] << endl;
	}*/

};


Block BlockGeneratorBase::generateBlock() {

vector<Block> blocks = this->getParsedBlocks();

for(int i = 0; i != blocks.size(); ++i){
	cerr << blocks[i].getName() << endl;
	vector<Cell> cells = blocks[i].getCells();
	for(int j = 0; j != cells.size(); ++j){
		cerr << cells[j].row << " " << cells[j].col << std::endl;
	}
}



int blockLen = blocks.size();
//cerr << this->sequence[this->currentIndex] << endl;

//if(!checkIfBlocksInSequenceExist(blocks)){
//	throw out_of_range("Block in sequence file was not parsed from Block files");
//}
//cout << this->sequence[this->currentIndex];
/*for(int i = 0; i != blockLen; ++i){
	if(blocks[i].getName() == this->sequence[this->currentIndex]){		
		if(this->currentIndex + 1 == this->numblocksInSequence){
			this->currentIndex = 0;
		} else{
			++(this->currentIndex); 
		}
		return blocks[i];
	}
}*/

//throw out_of_range("Block in sequence file was not parsed from Block files");
return Block();
}


//TODO
bool BlockGeneratorBase::checkIfBlocksInSequenceExist(std::vector<Block> blocks){
	return true;
}

void BlockGeneratorBase::parseSequence(){

	ifstream fin{this->sequenceFile};
	if(!fin.is_open()){
//		throw out_of_range("The file could not be opened");
	}
	string input;
	while(fin>>input){
		this->sequence.emplace_back("BLOCK-" + input);
	}
	fin.close();
}
