#include "Board.h"
#include "Cell.h"

#include <iostream>
using namespace std;

Board::Board(int width, int height): width{width}, height{height} {}

Cell Board::getInfo() const {
	return Cell();//TODO
}

void Board::notify(Subject &whoNotified) {

}

void Board::currentBlockLeft(int n) {
	currentBlock.moveLeft(n);
}

void Board::currentBlockRight(int n) {
	currentBlock.moveRight(n);
}

Block Board::generateBlock() {
	return blockFactory.generateBlock();
}

ostream &operator<<(std::ostream &out, const Board&b) {
	//cout << b.display; //display is no longer a method of board
	//use observer if you want it to display so bad
	return cout;
}
