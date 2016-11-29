#include "Board.h"
#include "Cell.h"
#include "subscriptions.h"
#include "info.h"

#include <iostream>
#include <vector>
using namespace std;

Board::Board(int width, int height): width{width}, height{height}, 
	blockFactory{BlockFactory()}, currentLevel{0} {
	currentBlock = blockFactory.generateBlock(this->currentLevel);
}

Info Board::getInfo() const {
	// calculate score here
	return Info{cells[0], cells[0], 0}; // Hack for now, fix later
}

void Board::notify(Subject &whoNotified) {

}

SubscriptionType Board::subType() const {
	return SubscriptionType::deadBlock;
}

void Board::currentBlockLeft(int n) {
	currentBlock.moveLeft(n);
}

void Board::currentBlockRight(int n) {
	currentBlock.moveRight(n);
}

void Board::currentBlockDown(int n) {
	currentBlock.moveDown(n);
}

void Board::currentBlockDrop() {
	
}

void Board::showHint(){

}

void Board::restart(){
	
}

void Board::currentBlockRotateClockwise(int n) {
	currentBlock.rotateClockWise(n);
}

void Board::currentBlockRotateCounterClockwise(int n) {
	currentBlock.rotateCounterClockWise(n);
}

void Board::setLevel(int n){
	currentLevel = n;
}

void Board::setCurrentBlock(string blockName){
	currentBlock = blockFactory.generateBlock(blockName);
}

	void Board::noRandomBlock(std::string file){
		blockFactory.noRandomBlock(file);
	}
	void Board::restoreRandom(){
		blockFactory.restoreRandom();
	}
	void Board::setSeed(int seed){
		blockFactory.setSeed(seed);
	}
	void Board::setSequence(std::string sequenceFile){
		blockFactory.setSequenceFile(sequenceFile);
	}


Block Board::generateBlock() { // may be useless
	return blockFactory.generateBlock(this->currentLevel);
}


