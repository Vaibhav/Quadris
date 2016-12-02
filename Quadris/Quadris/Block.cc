#include "Block.h"
#include "subscriptions.h"
#include "info.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;


// NOTE: height and width start at zero (ie. I-block has height 0)
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

void Block::rotateClockWise(int restraint) {
	if (lowerLeft.second + height >= restraint) return;
	prevCells = cells;
	for (auto &i:coords) {
		int row = i.first;
		int col = i.second;
		i.first = col;
		i.second = height - row;
	}
	rotateUpdate();	
}

void Block::clearBlockFromScreen(){
	prevCells = cells;
	cells.clear();
	notifyObservers(SubscriptionType::blockChange);
}

void Block::rotateCounterClockWise(int restraint) {
	if (lowerLeft.second + height >= restraint) return;
	prevCells = cells;
	for (auto &i:coords) {
		int row = i.first;
		int col = i.second;
		i.first = width - col;
		i.second = row;
	}
	rotateUpdate();
}

void Block::moveLeft() {
	if (lowerLeft.second <= 0) return;
	prevCells = cells;
	for (auto &i:cells) i.col -= 1;
	lowerLeft.second -= 1;
	notifyObservers(SubscriptionType::blockChange);
}

void Block::moveRight(int restraint) {
	if (lowerLeft.second + width + 1 >= restraint) return;
	prevCells = cells;
	for (auto &i:cells) i.col += 1;
	lowerLeft.second += 1;
	notifyObservers(SubscriptionType::blockChange);
}

vector<Cell> Block::getCells() const {
	return this->cells;
}

bool Block::moveDown(int restraint) {
	prevCells = cells;
	if (lowerLeft.first + 1 >= restraint) return false;
	for (auto &i:cells) i.row += 1;
	lowerLeft.first += 1;
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
	bool printed = false;
	for (int i = 0; i <= b.height; i++) {
		for (int j = 0; j <= b.width; j++) {
			for (auto k:b.coords) {
				if (k.first == i && k.second == j) {
					out << b.dispChar;
					printed = true;
				}
			}
			if(!printed) out << ' ';
		}
		endl(out);
	}
	return out;
}


int Block::deleteCells(int theRow, int theCol){

	int size = cells.size();
	for(int i =0; i < size; i++){
		if (cells[i].row == theRow && cells[i].col == theCol) {
			//remove from cells vector 
			this->cells.erase(cells.begin()+i);
		}
	}

	if ( !(this->cells.empty()) ){
		return this->level;
	} else {
		return -1;
	}

}

int Block::getHeight() const {
	return height;
}

int Block::getWidth() const {
	return width;
}

