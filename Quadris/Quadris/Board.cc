#include "Board.h"
#include "Cell.h"
#include "subscriptions.h"
#include "info.h"
#include <iostream>
#include <vector>
#include "BlockFactory.h"
using namespace std;


Board::Board(Display* d, int width, int height, string sequenceFile): 
	width{width}, height{height}, 
	blockFactory{BlockFactory()}, currentLevel{0} {
	//Propertly initialize blockFactory;
	//blockFactory.setLevel(currentLevel);
	blockFactory.setSequenceFile(sequenceFile);
	currentBlock = blockFactory.generateBlock(this->currentLevel);
	cerr << currentBlock.getName();
	currentBlock = blockFactory.generateBlock(this->currentLevel);
	cerr << currentBlock.getName();
	currentBlock = blockFactory.generateBlock(this->currentLevel);
	cerr << currentBlock.getName();
	currentBlock = blockFactory.generateBlock(this->currentLevel);
	cerr << currentBlock.getName();
	currentBlock = blockFactory.generateBlock(this->currentLevel);
	cerr << currentBlock.getName();
	currentBlock = blockFactory.generateBlock(this->currentLevel);
	cerr << currentBlock.getName();
	currentBlock = blockFactory.generateBlock(this->currentLevel);
	cerr << currentBlock.getName();
	currentBlock = blockFactory.generateBlock(this->currentLevel);
	cerr << currentBlock.getName();
	currentBlock = blockFactory.generateBlock(this->currentLevel);
	cerr << currentBlock.getName();
	currentBlock = blockFactory.generateBlock(this->currentLevel);
	cerr << currentBlock.getName();
	currentBlock = blockFactory.generateBlock(this->currentLevel);
	cerr << currentBlock.getName();
	currentBlock = blockFactory.generateBlock(this->currentLevel);
	cerr << currentBlock.getName();
	currentBlock = blockFactory.generateBlock(this->currentLevel);
	cerr << currentBlock.getName();
	currentBlock = blockFactory.generateBlock(this->currentLevel);
	cerr << currentBlock.getName();
	currentBlock = blockFactory.generateBlock(this->currentLevel);
	cerr << currentBlock.getName();

		currentBlock = blockFactory.generateBlock(1);
	cerr << currentBlock.getName();
			currentBlock = blockFactory.generateBlock(1);
	cerr << currentBlock.getName();
			currentBlock = blockFactory.generateBlock(1);
	cerr << currentBlock.getName();
			currentBlock = blockFactory.generateBlock(1);
	cerr << currentBlock.getName();
			currentBlock = blockFactory.generateBlock(1);
	cerr << currentBlock.getName();
			currentBlock = blockFactory.generateBlock(1);
	cerr << currentBlock.getName();
			currentBlock = blockFactory.generateBlock(1);
	cerr << currentBlock.getName();
			currentBlock = blockFactory.generateBlock(1);
	cerr << currentBlock.getName();
			currentBlock = blockFactory.generateBlock(1);
	cerr << currentBlock.getName();
			currentBlock = blockFactory.generateBlock(1);
	cerr << currentBlock.getName();


	// Idk wtf all the shit above is, but we need this:
	currentBlock.attach(d);
	currentBlock.notifyObservers(SubscriptionType::blockChange);
	
	
}


Info Board::getInfo() const {
	// calculate score here
	return Info{cells, cells, 0}; // Hack for now, fix later
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
	currentBlock.moveDown(n, height);
}


bool Board::canMoveDown() const {
	
	// Cells in the block
	vector<Cell> blockCells = currentBlock.getCells();
	
	// check if there are any cells in the board that are 1 row below that cell
	for (auto i: blockCells) {

		for (auto n : cells) {
		// check if cell below cell in block exists
			if (n.row == i.row + 1 && n.col == i.col){
				return false;
			}
		}
	} 
	
	// if cell doesn't exist returns true
	return true;
}

void Board::currentBlockDrop() {

	// keep moving block down until it can't move down
	while(canMoveDown()) {
		if (currentBlock.moveDown(1, height));
		else break;
	}
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


std::vector<int> Board::checkIfRowsComplete() {
	
}


void Board::clearRow(int row) {
	
}

