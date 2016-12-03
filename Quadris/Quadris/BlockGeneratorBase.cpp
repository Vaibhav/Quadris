#include "BlockGeneratorBase.h"
#include <string>   
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

BlockGeneratorBase::BlockGeneratorBase(string file): sequenceFile{file}, BlockGenerator{} {
	this->sequence = vector<string>{};
	parseSequence();
	this->currentIndex = 0;
	this->numblocksInSequence = this->sequence.size();

	for(int i  = 0; i != sequence.size(); ++i){
		cout << sequence[i];
	}

};


Block BlockGeneratorBase::generateBlock() {

vector<Block> blocks = this->getParsedBlocks();


for(int i = 0; i != blocks.size(); ++i){
	cout<< blocks[i].getName();
}



int blockLen = blocks.size();
//cerr << this->sequence[this->currentIndex] << endl;


/*
if(!checkIfBlocksInSequenceExist(blocks)){
	throw out_of_range("Block in sequence file was not parsed from Block files");
}
*/
/*
//cout << this->sequence[this->currentIndex];
for(int i = 0; i != blockLen; ++i){
	if(blocks[i].getName() == this->sequence[this->currentIndex]){		
		if(this->currentIndex + 1 == this->numblocksInSequence){
			this->currentIndex = 0;
		} else{
			++(this->currentIndex); 
		}
		cerr << blocks[i].getName();
		return blocks[i];
	}
}
*/

	Block generatedBlock = BlockGenerator::generateBlock(this->sequence[this->currentIndex]);
	++(this->currentIndex); 
	return generatedBlock;

}

/*
bool BlockGeneratorBase::checkIfBlocksInSequenceExist(std::vector<Block> blocks){
	int size = sequence.size();
	int numBlocksParsed = blocks.size();
	bool found = false;
for(int i = 0; i != size ; ++i ){
	for(int j = 0; j != numBlocksParsed; ++j){
		if(blocks[j].getName() == sequence[i]) {
			cout << blocks[j].getName() << " fcking " << sequence[i];
			found = true;
			break;
		}
	}
	if(found == false){
		return false; 
	} else {
		found = false;
	}
}
	return true;
}
*/

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
