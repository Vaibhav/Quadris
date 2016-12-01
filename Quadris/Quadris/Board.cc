#include "Board.h"
#include "Cell.h"
#include "subscriptions.h"
#include "info.h"
#include <iostream>
#include <vector>
#include "BlockFactory.h"
using namespace std;


Board::Board(int width, int height, string sequenceFile): width{width}, height{height}, 
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
	currentBlock.moveDown(n);
}


bool Board::canMoveDown() {
	
	vector<Cell> blockCells = currentBlock.getCells();
	// the higher the number the lower the row 
	int lowestRow = 0;
	int colOflowestCell = 0; 


	// find lowest cell in current block
	for (int i = 0; i < blockCells.size(); i++) {

		if (blockCells[i].row > lowestRow){
			lowestRow = blockCells[i].row;
			colOflowestCell = blockCells[i].col; 
		} 

	}
	
	// check if there are any cells in the board that are 1 row blow that cell
	for (int n; n < this->cells.size(); n++){
		// check if cell below lowest cell in block exists
		if (cells[n].row == lowestRow + 1 && cells[n].col == colOflowestCell) {
			return false; 
		}
	} 
	
	// if cell doesn't exist returns true
	return true;
}

void Board::currentBlockDrop() {

	// keep moving block down until it can't move down
	while(canMoveDown()) {
		currentBlock.moveDown(1);
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

