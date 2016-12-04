#include "Board.h"
#include "Cell.h"
#include "subscriptions.h"
#include "info.h"
#include <iostream>
#include <vector>
#include "BlockFactory.h"
#include <algorithm>
using namespace std;

void Board::attachAndNotify(shared_ptr<Block> b) {
	b->attach(display);
	if (!textMode) b->attach(gd);
	b->notifyObservers(SubscriptionType::blockChange);
}

void Board::initialize(string sequenceFile, int seed) {
	//Propertly initialize blockFactory;
	//blockFactory.setLevel(currentLevel);
	setSequence(sequenceFile);
	setSeed(seed);
	currentBlock = generateBlock();
 	nextBlock = generateBlock();
	// Idk wtf all the shit above is, but we need this:

	//cout << currentBlock->getLevel() << endl;
	//cout << nextBlock->getLevel() << endl;

	attachAndNotify(currentBlock);
}


Board::Board(TextDisplay* d, GraphicDisplay *gd, string sequenceFile, 
	int startLevel, int seed, bool textMode, int width, int height ):
	display{d}, gd{gd}, blockFactory{BlockFactory()}, 
	currentLevel{startLevel}, textMode{textMode}
	{ 
		setHeight(height);
		setWidth(width);
		initialize(sequenceFile, seed) ;
	}


Info Board::getInfo() const {
	// calculate score here
	return Info{cells, cells, 0}; // Hack for now, fix later
}


void Board::setHeight(int n){
	blockFactory.setBoardHeight(n);
	this->height = n;
}

void Board::setWidth(int n){
	blockFactory.setBoardWidth(n);
	this->width = n;
}

void Board::notify(Subject &whoNotified) {

}


SubscriptionType Board::subType() const {
	return SubscriptionType::deadBlock;
}


void Board::currentBlockLeft(int n) {
	for (int i=0; i< n; i++) {
		if (!canMoveLeft()) return;
		currentBlock->moveLeft();
	}
}

void Board::currentBlockRight(int n) {
	for (int i=0; i< n; i++) {
		if (!canMoveRight()) return;
		currentBlock->moveRight(width);
	}
}


void Board::currentBlockDown(int n) {
	for (int i=0; i< n; i++) {
		if (!canMoveDown()) return;
		currentBlock->moveDown(height);
	}
}


bool Board::canMoveDown() const {
	// Cells in the block
	vector<Cell> blockCells = currentBlock->getCells();

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

pair<int, vector<int>> Board::currentBlockDrop() {

	// keep moving block down until it can't move down
	while(canMoveDown() && currentBlock->moveDown(height)) {}

	// update cells vector
	for (auto i:currentBlock->getCells()) {
		cells.push_back(i);
	}

	// updates blocks vector
	blocks.push_back(currentBlock);

	// check if any row is completed
	vector<int> rowsCompleted = checkIfRowsComplete();
	pair<int, vector<int>> toReturn;

	if ( !(rowsCompleted.empty()) ){
		int numOfRows = rowsCompleted.size();
		// clear the rows
		vector<int> listOfLevels = clearRows(rowsCompleted);

		// move everything down
		shiftBoardDown(rowsCompleted);

		toReturn.first = numOfRows;
		toReturn.second = listOfLevels;

	} else {
		toReturn.first = 0;
		toReturn.second = vector<int>();
	}


	return toReturn;
}

void Board::showHint(){ // Hackiest function we got
	vector<pair<int,int>> sqrs;
	shared_ptr <Block> tempBlock = currentBlock;
	for (auto i:currentBlock->getCells()) {
		sqrs.emplace_back(i.row-3, i.col);
	}
	currentBlock = make_shared<Block> (Block{'?', "Black", "Hint", sqrs});
	int highestRow;
	vector<int> topCols;
	for (auto i:cells) {
		if (i.row < highestRow) highestRow = i.row;
	}
	for (auto i:cells) {
		if (i.row == highestRow) topCols.push_back(i.col);
	}
	sort(topCols.begin(), topCols.end());
	topCols.push_back(width); // Add extra "column" at the end
	int tcSize = topCols.size();
	int biggestGap = 0;
	int gapStart = 0;
	for (int j=0; j < tcSize-1; j++) {
		if (topCols[j+1] - topCols[j] > biggestGap) {
			biggestGap = topCols[j+1] - topCols[j];
			gapStart = topCols[j];
		}
	}
	if (biggestGap > currentBlock->getWidth()) {
		int hbpos = currentBlock->getLowerLeft().second;
		int horShift = gapStart + 1 - hbpos;
		if (horShift <  0) currentBlockLeft(-horShift);
		else currentBlockRight(horShift);
	}
	currentBlockDown(99); // Place hint Block
	hintBlock = currentBlock;
	currentBlock = tempBlock;	// Reset currentBlock
	attachAndNotify(hintBlock);
}

void Board::clearHint() {
	hintBlock->clearBlockFromScreen();
}


void Board::restart(){

	vector<int> v;
	// Clear all rows
	for(int i = 0; i < this->height; i++) {
		v.emplace_back(i);
	}
	clearRows(v);

	// Reset Blocks
	currentBlock->clearBlockFromScreen();
}


void Board::currentBlockRotateClockwise(int n) {
	for (int i=0; i< n; i++) {
		if (!canRotateCW()) return;
		currentBlock->rotateClockWise(width);
	}
}


void Board::currentBlockRotateCounterClockwise(int n) {
	for (int i=0; i< n; i++)  {
		if (!canRotateCW()) return;
		currentBlock->rotateCounterClockWise(width);
	}
}


void Board::setLevel(int n){
	currentLevel = n;
}


void Board::setCurrentBlock(string blockName){
	currentBlock->clearBlockFromScreen();
	currentBlock->detach(display);
	currentBlock = blockFactory.generateBlock(blockName, this->currentLevel);
	attachAndNotify(currentBlock);
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


std::shared_ptr<Block> Board::generateBlock() {
	return blockFactory.generateBlock(this->currentLevel);
}

// Called by Game, returns false if game over
bool Board::generate() {
	// get new current block
	currentBlock = nextBlock;
	// create next block
	nextBlock = generateBlock();

	for (auto i:cells) {
		for (auto j:currentBlock->getCells()) {
			if (i.row == j.row && i.col == j.col) {
				// End the game
				return false;
			}
		} 
	}

	attachAndNotify(currentBlock);
	return true;
}


// RIP
bool inVec(vector<int> anycontainer, int testvalue){
	bool contains = find(anycontainer.begin(), anycontainer.end(), testvalue) != anycontainer.end();
	return !contains;
}


// returns which rows are completed
vector<int> Board::checkIfRowsComplete() {

	vector<int> v;
	int counter = 0;
	int rows = this->height;

	for (int i = 0; i < rows; i++) {
		counter = 0;
		for (auto n: this->cells){
			if (n.row == i){
				counter++;
			}
		}
		if (counter >= width){
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

		 if ( !(lvls.empty()) ) {
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
	vector<int> index;
	vector<int> cols;

	int size = cells.size();
	for(int i = 0; i < size; i++) {
		if (cells[i].row == theRow && inVec(cols, cells[i].col)){
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


	for(auto n: toDelete){

		int cellRow = n.row;
		int cellCol = n.col;
		theLevel = getLevel(cellRow, cellCol, this->width);
		if (theLevel != -1) levels.emplace_back(theLevel);
	}

	return levels;
}


// gets the level on the block if deleted, else it returns -1
int Board::getLevel(int row, int col, int width) {
	int blockSize = blocks.size();

	for (int i =0; i < blockSize; i++) {
		for (unsigned int j = 0; j < blocks[i]->getCells().size(); j++) {
			// update the cell and if it deletes a block then it returns the level of the block
			if (blocks[i]->getCells()[j].row == row && blocks[i]->getCells()[j].col == col) {
				int x = blocks[i]->updateCells(row, width);
				return x;
			}

		}
	}
	return -1;
}

void Board::shiftBoardDown(vector<int> rows) {
	for (auto r:rows) {
		for (auto &i:cells) {
			if (i.row < r) i.row++;
		}
		int bs = blocks.size();
		for (int j=0; j < bs; j++) {
			blocks[j]->moveCellsAboveDown(r);
		}

	}
}


void Board::printNextBlock() {
	cout << *nextBlock;
}

void Board::printNextBlockGraphic(GraphicDisplay *gd) {
	nextBlock->nextBlockGraphicPls(gd);
}

bool Board::canMoveLeft() const {
	vector<Cell> blockCells = currentBlock->getCells();
	for (auto i: blockCells) {
		for (auto n : cells) {
			if (n.row == i.row && n.col == i.col - 1) return false;
		}
	}
	return true;
}

bool Board::canMoveRight(int k) const {
	vector<Cell> blockCells = currentBlock->getCells();
	for (auto i: blockCells) {
		for (auto n : cells) {
			if (n.row == i.row && n.col == i.col + k) return false;
		}
	}
	return true;
}

bool Board::canRotateCW() const {
	int h = currentBlock->getHeight();
	int w = currentBlock->getWidth();
	pair<int,int> lowerLeft = currentBlock->getLowerLeft();
	for (int i=0; i <= w; i++) {
		for (int j=0; j <= h; j++) {
			for (auto k:cells) {
				if (k.row == lowerLeft.first-i && 
					k.col == lowerLeft.second+j) return false;
			}
		}
	}
	return true;
}

/*bool Board::canRotateCCW() const {
	int h = currentBlock->getHeight();
	bool flag = false;
	for (int i=1; i <= h; i++) {
		if (!canMoveRight(i)) flag = true;
	}
	if (flag && h > currentBlock->getWidth()) return false;
	return true;
}*/

void Board::addCentreBlock() {
	// Add block next available row
	int col = width / 2;
	int highestRow = height-1;
	for(auto i:cells) {
		if (i.row < highestRow && i.col == col) {
			highestRow = i.row;
		}
	}
	// Make sure we're not at the top
	if (highestRow <= 0) return;
	cells.push_back(Cell{'*', highestRow-1, col});
	vector<pair<int, int>> sqr{{highestRow-1, col}};
	std::shared_ptr<Block> centreBlock {new Block{'*', "Brown", "Centre", sqr}};
	cout << "CENTRE BLOCK CREATED" << endl;
	blocks.push_back(centreBlock);
	attachAndNotify(centreBlock);
}
