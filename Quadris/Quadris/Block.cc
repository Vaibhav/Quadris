#include "Block.h"
#include "subscriptions.h"
#include "info.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;

int calcHeight(std::vector < std::pair < int, int > > coords) {
	int highest = 0;
	for (auto i:coords) {
		if (i.first > highest) highest = i.first;
	}
	return highest;
}

int calcWidth(std::vector < std::pair < int, int > > coords) {
	int highest = 0;
	for (auto i:coords) {
		if (i.second > highest) highest = i.second;
	}
	return highest;
}

pair<int, int> Block::findLowest() {
	int furthestLeft = cells[0].col;
	int furthestDown = cells[0].row;
	for (auto i:cells) {
		if (i.col < furthestLeft) furthestLeft = i.col;
		if (i.row > furthestDown) furthestDown = i.row;
	}
	pair<int,int> p2{furthestDown, furthestLeft};
	return p2;
}

//This is for the block parser
Block::Block(char dispChar, 
	 	  std::string colour, 
		  std::string name,
		  std::vector < std::pair < int, int > > coords
		  ): colour(colour), name(name), coords(coords), dispChar(dispChar) {

	for (auto i:coords) { 
		cells.push_back(Cell{this, dispChar, i.first+3, i.second});
	} // Add 3 to le height for safety purposes

	height = calcHeight(coords);
	width = calcWidth(coords);
	
	lowerLeft = findLowest();

	notifyObservers(SubscriptionType::blockChange);
}

Block::Block() {} // default ctor

void Block::rotateUpdate() {
	int csize = cells.size();
	for (int i=0; i < csize; i++) { // cannot use auto here
		cells[i].row = lowerLeft.first -width + coords[i].first;
		cells[i].col = lowerLeft.second + coords[i].second;
		cout << lowerLeft.first << endl;
	}
	lowerLeft = findLowest();
	height = calcHeight(coords);
	width = calcWidth(coords);
	notifyObservers(SubscriptionType::blockChange);
}

void Block::rotateClockWise(int n) {
	prevCells = cells;
	for (auto &i:coords) {
		int row = i.first;
		int col = i.second;
		i.first = col;
		i.second = height - row;
	}
	rotateUpdate();	
}

void Block::rotateCounterClockWise(int n) {
	prevCells = cells;
	for (auto &i:coords) {
		int row = i.first;
		int col = i.second;
		i.first = width - col;
		i.second = row;
	}
	rotateUpdate();
}

void Block::moveLeft(int n) {
	prevCells = cells;
	for (auto &i:cells) i.col -= n;
	lowerLeft.second -= n;
	notifyObservers(SubscriptionType::blockChange);
}

void Block::moveRight(int n) {
	prevCells = cells;
	for (auto &i:cells) i.col += n;
	lowerLeft.second += n;
	notifyObservers(SubscriptionType::blockChange);
}

vector<Cell> Block::getCells(){
	return this->cells;
}

bool Block::moveDown(int n, int restraint) {
	prevCells = cells;
	if (lowerLeft.first + n >= restraint) return false;
	for (auto &i:cells) i.row += n;
	lowerLeft.first += n;
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

ostream &operator<<(std::ostream &out, const Block&b) {
	int curRow = 0;
	int curCol = 0;
	for (auto i:b.coords) {
		if (i.first > curCol) {
			curCol ++;
			endl(out);
		}
		if (i.second > curRow) {
			curRow ++;
			cout << ' ';
		}
		cout << b.dispChar;
	}
}

