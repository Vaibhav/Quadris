#include "Board.h"
#include "Cell.h"
#include "subscriptions.h"
#include "info.h"
#include <iostream>
#include <vector>
#include "BlockFactory.h"
using namespace std;


Board::Board(Display* d, int width, int height, string sequenceFile): 
	width{width}, height{height}, display{d},
	blockFactory{BlockFactory()}, currentLevel{0} {
	//Propertly initialize blockFactory;
	//blockFactory.setLevel(currentLevel);
	blockFactory.setSequenceFile(sequenceFile);
	/*
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
	*/
/*	currentBlock = blockFactory.generateBlock(1);
	cerr << currentBlock.getName();
	currentBlock = blockFactory.generateBlock(1);
	cerr << currentBlock.getName();
	currentBlock = blockFactory.generateBlock(1);
	cerr << currentBlock.getName();
	currentBlock = blockFactory.generateBlock(1);
	cerr << currentBlock.getName();
	*/
/*			currentBlock = blockFactory.generateBlock(1);
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
	cerr << currentBlock.getName();*/
			currentBlock = blockFactory.generateBlock(1);
	//cerr << currentBlock.getName();
			nextBlock = blockFactory.generateBlock(1);

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


bool Board::canMoveDown() {
	
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

	// update cells vector 
	for (auto i:currentBlock.getCells()) {
		cells.push_back(i);
	}

	// updates blocks vector 
	blocks.push_back(currentBlock);

	// check if any row is completed
	vector<int> rowsCompleted = checkIfRowsComplete();

	if ( !(rowsCompleted.empty()) ){
		
		// clear the rows
		vector<int> listOfLevels = clearRows(rowsCompleted);
		// update score
		// Game::updateScore();

	}
	
 	
	
	// get new current block
	currentBlock = nextBlock;
	// create next block
	nextBlock = generateBlock();
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

//HIJACKED FUNCTIONALITY CHANGE BACK LATER
void Board::setCurrentBlock(string blockName){
//	currentBlock = blockFactory.generateBlock(this->currentLevel);
//	cerr << currentBlock.getName() << endl;
//	currentBlock = blockFactory.generateBlock(blockName);
	currentBlock = blockFactory.generateBlock(blockName);
	currentBlock.attach(this->display);
	currentBlock.notifyObservers(SubscriptionType::blockChange);
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


// RIP 

// returns which rows are completed
vector<int> Board::checkIfRowsComplete() {
	
	vector<int> v;
	int counter = 0; 
	//const int width;
	int rows = this->height;

	for (int i = 0; i < rows; i++) {
		for (auto n: this->cells){
			if (n.row == i) {
				counter++;
			}
		}

		if (counter == width){
			v.emplace_back(i);
		}
	}

	return v; 
}

vector<int> Board::clearRows(vector<int> rowsCompleted) {

	vector<int> lvls;
	vector<int> listOfLevels; 

	for (auto i: rowsCompleted) {
		 lvls = clearRow(i);

		 if ( !(lvl.empty()) ) {
		 	for (auto n: lvls) {
		 		listOfLevels.emplace_back(n);
		 	}
		 }
	}

	return listOfLevels;

}

vector<int> Board::clearRow(int theRow) {
	
	// vector of cells that need to be deleted 
	vector<Cell> toDelete;
	int theLevel;
	vector<int> levels; 

	for(auto i: this->cells){
		if (i.row = theRow){
			toDelete.emplace_back(i);
			this->cells.erase(i);
		}

	}

	for(auto n: toDelete){

		int cellRow = n.row;
		int cellCol = n.col;
		theLevel = n.blockPtr->deleteCell(cellRow, cellCol);
		if (theLevel != -1) levels.emplace_back(theLevel);

	}

	return theLevel;

}


void Board::printNextBlock() {
	cout << nextBlock;
}
