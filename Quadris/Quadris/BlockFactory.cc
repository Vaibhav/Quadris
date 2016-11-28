#include "BlockFactory.h"
#include "Block.h"

using namespace std;

Block BlockFactory::generateBlock(int level) {
	return Block();
}

Block BlockFactory::generateBlock(string blockName) {
	return Block();
}

	void BlockFactory::setSeed(int n){
		seed = n;
	}
	
	void BlockFactory::setSequenceFile(std::string sequenceFile){
		this->sequenceFile = sequenceFile;
	}

	void BlockFactory::noRandomBlock(std::string file){
		this->noRandom = true;
		this->noRandomBlockFile = file;
	}

	void BlockFactory::restoreRandom(){
		this->noRandom = false;
		this->noRandomBlockFile = "";
	}