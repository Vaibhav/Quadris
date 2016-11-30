#include "GeneratorProbabilityDecorator.h"
#include <string>   
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

BlockGeneratorBase::BlockGeneratorBase(string file): sequenceFile{file} {
	this->sequence = vector<string>{};
	parseSequence();
	this->currentIndex = 0;
	this->numblocksInSequence = this->sequence.size();
};


Block BlockGeneratorBase::generateBlock(){
vector<Block> blocks = this->getParsedBlocks();

for(int i = 0; i != blocks.size(); ++i){
	if(blocks[i].getName() == this->sequence[this->currentIndex]){		
		if(this->currentIndex + 1 == this->numblocksInSequence){
			this->currentIndex = 0;
		} else{
			++this->currentIndex; 
		}
		return blocks[i];
	}
}

throw out_of_range("Block in sequence file did not parse from Block files");

}


//TODO
bool BlockGeneratorBase::checkIfBlocksInSequenceExist(std::vector<Block> blocks){
	return true;
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