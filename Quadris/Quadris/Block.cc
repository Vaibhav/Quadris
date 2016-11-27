#include "Block.h"
#include <string>
#include <vector>
using namespace std;

Block::Block(char dispChar, string colour, int level): 
	colour{colour}, level{level} {
	int r = 3;
	int c = 0;
	for (int i=0; i < 4; i++, r++) { 
		cells.push_back(Cell{this, dispChar, r, c});
	}
	notifyObservers();
}

Block::Block() {} // default ctor

void Block::rotateClockWise() {
	int leftRow = lowerLeft.row;
	int leftCol = lowerLeft.col;
	for (int i = 0; i < cells.size(); i++) {
		int rowt = cells[i].row;
		int colt = cells[i].col;
		cells[i].row = leftRow - height + colt;
		cells[i].col = leftCol - width + rowt;
	}
}

void Block::rotateCounterClockWise() {

}

void Block::moveLeft() {
	for (int i=0; i < cells.size(); i++) {
		cells[i].col -= 1;
	}
	lowerLeft.col -= 1;
}

void Block::moveRight() {
	for (int i = 0; i < cells.size(); i++) {
		cells[i].col += 1;
	}
	lowerLeft.col -= 1;
}

Cell Block::getInfo() const {

}

Block::~Block() {}
