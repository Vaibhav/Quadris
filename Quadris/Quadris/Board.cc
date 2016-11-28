#include "Board.h"
#include "Cell.h"
#include "subscriptions.h"

#include <iostream>
using namespace std;

Board::Board(int width, int height): width{width}, height{height}, blockFactory{BlockFactory()} {}

Cell Board::getInfo() const {
	return Cell();//TODO
}

void Board::notify(Subject &whoNotified) {

}

SubscriptionType Board::subType() const {
	return SubscriptionType::deadBlock;
}

void Board::currentBlockLeft(int n) {
	currentBlock.moveLeft(n);
}

void Board::currentBlockRight(int n) {
	currentBlock.moveRight(n);
}

void Board::currentBlockDown(int n) {
	currentBlock.moveDown(n);
}

void Board::currentBlockRotateClockwise(int n) {
	currentBlock.rotateClockWise(n);
}

void Board::currentBlockRotateCounterClockwise(int n) {
	currentBlock.rotateCounterClockWise(n);
}

void Board::setLevel(int n){
	currentLevel = n;
}

void Board::setCurrentBlock(string blockName){
	currentBlock = blockFactory.generateBlock(blockName);
}

Block Board::generateBlock() {
	return blockFactory.generateBlock(this->currentLevel);
}


