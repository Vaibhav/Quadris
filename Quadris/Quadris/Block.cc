#include "Block.h"
#include "subscriptions.h"
#include "info.h"
#include <string>
#include <vector>
#include <iostream> //debug
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

int calcHeight(std::vector < std::pair < int, int > > coords) {
	int highest = 0;
	int lowest = 0;
	for (auto i:coords) {
		if (i.first > highest) highest = i.first;
		if (i.first < lowest) lowest = i.first;
	}
	return highest - lowest;
}

int calcWidth(std::vector < std::pair < int, int > > coords) {
	int highest = 0;
	int lowest = 0;
	for (auto i:coords) {
		if (i.second > highest) highest = i.second;
		if (i.second < lowest) lowest = i.second;
	}
	return highest - lowest;
}

//This is for the block parser
Block::Block(char dispChar, 
	 	  std::string colour, 
		  std::string name,
		  std::vector < std::pair < int, int > > coords
		  ): colour(colour), name(name), coords(coords) {

	for (auto i:coords) { 
		cells.push_back(Cell{this, dispChar, i.first, i.second});
	}

	height = calcHeight(coords);
	width = calcWidth(coords);
	
	lowerLeft = findLowest(dispChar);

	notifyObservers(SubscriptionType::blockChange);
}

Block::Block() {} // default ctor

void Block::rotateUpdate() {
	int csize = cells.size();
	for (int i=0; i < csize; i++) { // cannot use auto here
		cells[i].row = lowerLeft.row + coords[i].first;
		cells[i].col = lowerLeft.col + coords[i].second;
	}
	notifyObservers(SubscriptionType::blockChange);
}

void Block::rotateClockWise(int n) {
	prevCells = cells;
	for (auto &i:coords) {
		int row = i.first;
		int col = i.second;
		i.first = col;
		i.second = width - row;
	}
	rotateUpdate();	
}

void Block::rotateCounterClockWise(int n) {
	prevCells = cells;
	for (auto &i:coords) {
		int row = i.first;
		int col = i.second;
		i.first = height - col;
		i.second = row;
	}
	rotateUpdate();
}

void Block::moveLeft(int n) {
	prevCells = cells;
	for (auto &i:cells) i.col -= n;
	lowerLeft.col -= n;
	notifyObservers(SubscriptionType::blockChange);
}

void Block::moveRight(int n) {
	prevCells = cells;
	for (auto &i:cells) i.col += n;
	lowerLeft.col += n;
	notifyObservers(SubscriptionType::blockChange);
}

vector<Cell> Block::getCells(){
	return this->cells;
}

bool Block::moveDown(int n, int restraint) {
	prevCells = cells;
	if (lowerLeft.row + n >= restraint) return false;
	for (auto &i:cells) i.row += n;
	lowerLeft.row += n;
	notifyObservers(SubscriptionType::blockChange);
	return true;
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

ostream &operator<<(std::ostream &out, const Block&b) {

}

