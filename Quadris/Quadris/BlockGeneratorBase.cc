#include "BlockGeneratorBase.h"
#include <string>   
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

BlockGeneratorBase::BlockGeneratorBase(string file): BlockGenerator{}, sequenceFile{file} {
	this->sequence = vector<string>{};
	parseSequence();
	this->currentIndex = 0;
	this->numblocksInSequence = this->sequence.size();
};


std::shared_ptr<Block> BlockGeneratorBase::generateBlock() {

vector<std::shared_ptr<Block>> blocks = this->getParsedBlocks();

	std::shared_ptr<Block> generatedBlock = BlockGenerator::generateBlock(this->sequence[this->currentIndex]);
	if(this->currentIndex + 1 == this->numblocksInSequence){
			this->currentIndex = 0;
		} else{
			++(this->currentIndex); 
		}
	return std::shared_ptr<Block>{generatedBlock};
}

void BlockGeneratorBase::parseSequence(){
	ifstream fin{this->sequenceFile};
	if(!fin.is_open()){
		throw out_of_range("The file could not be opened");
	}
	string input;
	while(fin>>input){
		this->sequence.emplace_back("BLOCK-" + input);
		
	}
	fin.close();
}

