#include "Board.h"
#include "Info.h"

#include <iostream>
using namespace std;

Board::Board(int width, int height): 
	display{Display(width, height)}, width{width}, height{height} {}

Info Board::getInfo() const {
	
}

void Board::notify(Subject &whoNotified) {

}

void Board::currentBlockLeft() {
	currentBlock.moveLeft();
}

void Board::currentBlockRight() {
	currentBlock.moveRight();
}

ostream &operator<<(std::ostream &out, const Board&b) {
	cout << b.display;
}
