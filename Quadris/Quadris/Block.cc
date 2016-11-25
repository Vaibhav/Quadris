#include "Block.h"
//#include "Info.h"
class Info;

void set2fook() {

}

void Block::rotateClockWise() {
	int leftRow = lowerLeft.row;
	int leftCol = lowerLeft.col;
	for (int i = 0; i < Cells.size(); i++) {
		int rowt = Cells[i].row;
		int colt = Cells[i].col;
		Cells[i].row = leftRow - height + colt;
		Cells[i].col = leftCol - width + rowt;
	}
}

void Block::rotateCounterClockWise() {

}

void Block::moveLeft() {
	for (int i=0; i < Cells.size(); i++) {
		Cells[i].col -= 1;
	}
	lowerLeft.col -= 1;
}

void Block::moveRight() {
	for (int i = 0; i < Cells.size(); i++) {
		Cells[i].col += 1;
	}
	lowerLeft.col -= 1;
}

Cell Block::getInfo() const {

}

Block::~Block() {}

Block::Block() {}
