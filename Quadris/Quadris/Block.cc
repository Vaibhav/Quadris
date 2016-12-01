#include "Block.h"
#include "subscriptions.h"
#include "info.h"
#include <string>
#include <vector>
using namespace std;

/*Block::Block(char dispChar, string colour, int level): 
	colour{colour}, level{level} {
	int r = 3;
	int c = 0;
	for (int i=0; i < 4; i++, r++) { 
		cells.push_back(Cell{this, dispChar, r, c});
	}
	notifyObservers(SubscriptionType::blockChange);
}*/

//This is for the block parser
Block::Block(char dispChar, 
	 	  std::string colour, 
		  std::string name,
		  std::vector < std::pair < int, int > > coords
		  ): colour(colour), name(name) {

	for (auto i:coords) { 
		cells.push_back(Cell{this, dispChar, i.first, i.second});
	}
	
	lowerLeft = findLowest(dispChar);

	notifyObservers(SubscriptionType::blockChange);
}

Block::Block() {} // default ctor

void Block::rotateClockWise(int n) {
	prevCells = cells;
	int leftRow = lowerLeft.row;
	int leftCol = lowerLeft.col;
	for (auto i:cells) {
		int rowt = i.row;
		int colt = i.col;
		i.row = leftRow - height + colt;
		i.col = leftCol - width + rowt;
	}
	notifyObservers(SubscriptionType::blockChange);
}

void Block::rotateCounterClockWise(int n) {

}

void Block::moveLeft(int n) {
	prevCells = cells;
	for (int i=0; i < cells.size(); i++) {
		cells[i].col -= n;
	}
	lowerLeft.col -= n;
	notifyObservers(SubscriptionType::blockChange);
}

void Block::moveRight(int n) {
	prevCells = cells;
	for (int i = 0; i < cells.size(); i++) {
		cells[i].col += n;
	}
	lowerLeft.col += n;
	notifyObservers(SubscriptionType::blockChange);
}

vector<Cell> Block::getCells(){
	return this->cells;
}

void Block::moveDown(int n, int restraint) {
	prevCells = cells;
	if (lowerLeft.row + n > restraint) return;
	for (auto i:cells) i.row += n;
	lowerLeft.row += n;
	notifyObservers(SubscriptionType::blockChange);
}

Info Block::getInfo() const {
	return Info{prevCells, cells}; // Array of cells so display knows what to update
}

void Block::setLevel(int n){
	level = n;
}

string Block::getName(){
	return this->name;
}

Block::~Block() {}

Cell Block::findLowest(char displayChar){

	int lowestRow = 0; 
	int colOflowestCell; 

	for (auto i: this->cells) {
		if (i.row > lowestRow){
			lowestRow = i.row;
			colOflowestCell = i.col; 
		}
	}

	Cell newCell{this, displayChar, lowestRow, colOflowestCell};
	return newCell;

}