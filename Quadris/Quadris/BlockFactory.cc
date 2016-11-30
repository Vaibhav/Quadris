#include "BlockFactory.h"
#include "Block.h"
#include "BlockGeneratorBase.h"
#include <utility>
#include <memory>
#include <utility>

using namespace std;

//class std::unique_ptr<T>

Block BlockFactory::generateBlock(int level) {
	if(level == 0){
		//auto p = make_unique<new BlockGeneratorBase{}>;
	unique_ptr< BlockGenerator > p {new BlockGeneratorBase{sequenceFile}};
	return p->generateBlock();
	} else if (level == 1) {

	} else if(level == 2){

	} else if(level == 3){

	} else if(level ==  4){

	}
	//	return p->generateBlock();
	return Block();
}

Block BlockFactory::generateBlock(string blockName) {
	generateBlock();
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