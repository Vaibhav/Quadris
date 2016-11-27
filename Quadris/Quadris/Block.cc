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

void Block::rotateClockWise(int n) {
	int leftRow = lowerLeft.row;
	int leftCol = lowerLeft.col;
	for (int i = 0; i < cells.size(); i++) {
		int rowt = cells[i].row;
		int colt = cells[i].col;
		cells[i].row = leftRow - height + colt;
		cells[i].col = leftCol - width + rowt;
	}
}

void Block::rotateCounterClockWise(int n) {

}

void Block::moveLeft(int n) {
	for (int i=0; i < cells.size(); i++) {
		cells[i].col -= n;
	}
	lowerLeft.col -= n;
}

void Block::moveRight(int n) {
	for (int i = 0; i < cells.size(); i++) {
		cells[i].col += n;
	}
	lowerLeft.col -= n;
}


void Block::moveDown(int n) {
	for (int i = 0; i < cells.size(); i++) {
		cells[i].row -= n;
	}
	lowerLeft.row -= n;
}

Cell Block::getInfo() const {
	return Cell(); //TODO
}

Block::~Block() {}
