#include "Board.h"
#include "Cell.h"
#include "subscriptions.h"
#include "info.h"
#include <iostream>
#include <vector>
#include "BlockFactory.h"
#include <algorithm>
using namespace std;



Board::Board(TextDisplay* d, GraphicDisplay *gd, int width, int height, string sequenceFile): 
	display{d}, gd{gd}, blockFactory{BlockFactory()}, currentLevel{0},
	width{width}, height{height} {

	//Propertly initialize blockFactory;
	//blockFactory.setLevel(currentLevel);
	blockFactory.setSequenceFile(sequenceFile);
	currentBlock = blockFactory.generateBlock(1);
	nextBlock = blockFactory.generateBlock(1);

	// Idk wtf all the shit above is, but we need this:

	currentBlock.attach(d);
	currentBlock.attach(gd);
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
	for (int i=0; i< n; i++) {
		if (!canMoveLeft()) return;
		currentBlock.moveLeft();
	}
}

void Board::currentBlockRight(int n) {
	for (int i=0; i< n; i++) {
		if (!canMoveRight()) return;
		currentBlock.moveRight(width);
	}
}


void Board::currentBlockDown(int n) {
	for (int i=0; i< n; i++) {
		if (!canMoveDown()) return;
		currentBlock.moveDown(height);
	}
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
		if (currentBlock.moveDown(height));
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

	currentBlock.attach(display);
	currentBlock.attach(gd);
	currentBlock.notifyObservers(SubscriptionType::blockChange);

>>>>>>> origin/master
}

void Board::showHint(){

}


void Board::restart(){

}


void Board::currentBlockRotateClockwise(int n) {
	for (int i=0; i< n; i++) {
		if (!canRotateCW()) return;
		currentBlock.rotateClockWise(width);
	}
}


void Board::currentBlockRotateCounterClockwise(int n) {
	for (int i=0; i< n; i++)  {
		if (!canRotateCCW()) return;
		currentBlock.rotateCounterClockWise(width);
	}
}


void Board::setLevel(int n){
	currentLevel = n;
}

//HIJACKED FUNCTIONALITY CHANGE BACK LATER
void Board::setCurrentBlock(string blockName){
	currentBlock = blockFactory.generateBlock(this->currentLevel);
	cerr << currentBlock.getName() << endl;
	currentBlock = blockFactory.generateBlock(blockName);
<<<<<<< HEAD
//	currentBlock.clearBlockFromScreen();
//	currentBlock.detach(display);
//	currentBlock = blockFactory.generateBlock(blockName);
//	currentBlock.attach(this->display);
//	currentBlock.notifyObservers(SubscriptionType::blockChange);
=======
	currentBlock.attach(this->display);
	currentBlock.attach(this->gd);
	currentBlock.notifyObservers(SubscriptionType::blockChange);
>>>>>>> origin/master
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
bool inVec(vector<int> anycontainer, int testvalue){
	bool contains = find(anycontainer.begin(), anycontainer.end(), testvalue) != anycontainer.end();
	return !contains;
}


// returns which rows are completed
vector<int> Board::checkIfRowsComplete() {

	vector<int> v;
	vector<int> cols;
	int counter = 0;
	//const int width;
	int rows = this->height;

	for (int i = 0; i < rows; i++) {
		for (auto n: this->cells){
			if (n.row == i && inVec(cols, n.col)) {
				cols.emplace_back(n.col);
				counter++;
			}
		}
		if (counter == width){
			v.emplace_back(i);
		}
	}

	return v;
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
		// cout << "rows completed not empty" << endl;
		// clear the rows
		vector<int> listOfLevels = clearRows(rowsCompleted);
		// update score
		// Game::updateScore();

	}
	// get new current block
	currentBlock = nextBlock;
	// create next block
	nextBlock = generateBlock();

	currentBlock.attach(display);
	currentBlock.notifyObservers(SubscriptionType::blockChange);

}




vector<int> Board::clearRows(vector<int> rowsCompleted) {

	vector<int> lvls;
	vector<int> listOfLevels;

	for (auto i: rowsCompleted) {
		 cout << "clearRows: " << i << endl;
		 lvls = clearRow(i);

		 if ( !(lvls.empty()) ) {
		 	for (auto n: lvls) {
		 		listOfLevels.emplace_back(n);
		 	}
		 }
	}

	return listOfLevels;

}

vector<int> Board::clearRow(int theRow) {

	cout << "clearRow Called" << endl;
	// vector of cells that need to be deleted
	vector<Cell> toDelete;
	int theLevel;
	vector<int> levels;
	vector<int> index;
	vector<int> cols;

	int size = cells.size();
	for(int i =0; i < size; i++){
		if (cells[i].row == theRow && inVec(cols, cells[i].col)){
			cout << "row iter: " << i << endl;
			cout << "row: " << cells[i].row << " cols: " << cells[i].col << endl;
			toDelete.emplace_back(cells[i]);
			index.emplace_back(i);
			cols.emplace_back(cells[i].col);
		}
	}

	int size2 = index.size();

	for (int j = 0; j < size2; j++) {
		this->cells.erase(cells.begin()+index[j]);
		for (int i = j+1; i < size2;  i++) {
				index[i] -= 1;
		}
	}



	cout << "made it out of first loop" << endl;
	for(auto n: toDelete){

		cout << "0" << endl;
		int cellRow = n.row;
		cout << "1" << endl;
		cout << "2" << endl;
		//WELL FUCK
		theLevel = n.blockPtr->updateCells(cellRow, this->width);
		cout << "3" << endl;
		if (theLevel != -1) levels.emplace_back(theLevel);
		cout << "4" << endl;

	}

	return levels;

}


void Board::printNextBlock() {
	cout << nextBlock;
}

bool Board::canMoveLeft() const {

	vector<Cell> blockCells = currentBlock.getCells();
	for (auto i: blockCells) {
		for (auto n : cells) {
			if (n.row == i.row && n.col == i.col - 1) return false;
		}
	} 
	return true;
}

bool Board::canMoveRight(int k) const {
	vector<Cell> blockCells = currentBlock.getCells();
	for (auto i: blockCells) {
		for (auto n : cells) {
			if (n.row == i.row && n.col == i.col + k) return false;
		}
	} 
	return true;
}

bool Board::canRotateCW() const {
	int h = currentBlock.getHeight();
	bool flag = false;
	for (int i=1; i <= h; i++) {
		if (!canMoveRight(i)) flag = true;
	}
	if (flag && h > currentBlock.getWidth()) return false;
	return true;
}

bool Board::canRotateCCW() const {
	int h = currentBlock.getHeight();
	bool flag = false;
	for (int i=1; i <= h; i++) {
		if (!canMoveRight(i)) flag = true;
	}
	if (flag && h > currentBlock.getWidth()) return false;
	return true;
}
