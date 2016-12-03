#include "HeavyBlockDecorator.h"
#include "Block.h"

void HeavyBlockDecorator::rotateClockWise(int n) {
	Block::rotateClockWise(n);
	Block::moveDown(1);
}
	
void HeavyBlockDecorator::rotateCounterClockWise(int n) {
	Block::rotateCounterClockWise(n);
	Block::moveDown(1);
}


void HeavyBlockDecorator::moveDown(int n) {
	Block::moveDown(n+1);
}


void HeavyBlockDecorator::moveLeft(int n) {
	Block::moveLeft(n);
	Block::moveDown(1);
}

void HeavyBlockDecorator::moveRight(int n) {
	Block::moveRight(n);
	Block::moveDown(1);
}