#include "GeneratorProbabilityDecorator.h"
#include <string>   
#include <vector>
#include <algorithm>
#include <fstream>
#include <memory>

using namespace std;


GeneratorProbabilityDecorator::GeneratorProbabilityDecorator(std::shared_ptr<BlockGenerator> componenet)
:BlockGeneratorDecorator{component}{





}


Block GeneratorProbabilityDecorator::generateBlock(){
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


GenerateProbabilityDecorator::GenerateProbabilityDecorator(std::shared_ptr<BlockGenerator> component,
std::vector<string> blocks, std::vector<double> probabilities){
setProbability(blocks, probabilities);
}



void GenerateProbabilityDecorator::setProbability(std::vector<std::string> blocks, std::vector<double> probabilities){


int size = blocks.size();
pair<string, double> item;

if(blocks.size() != probabilities.size()){
	throw out_of_range("The list of blocks specified is not the same size as the list of probabilities specified");
}

for(int i = 0; i != size; ++i){
item.first = blocks[i];
item.second = probabilities[i];

this->blockProbabilities.emplace_back(item);
}



}



/*
//TODO
bool GeneratorProbabilityDecorator::checkIfBlocksInSequenceExist(std::vector<Block> blocks){
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
*/