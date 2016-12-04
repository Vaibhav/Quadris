#include "HeavyBlockDecorator.h"
#include "Block.h"
#include <memory>

HeavyBlockDecorator::HeavyBlockDecorator(std::shared_ptr<Block> component): BlockDecorator{component}{
}
/*
void HeavyBlockDecorator::rotateClockWise(int restraint) {
	component->rotateClockWise(restraint);
	Block::moveDown(1);
}
	
void HeavyBlockDecorator::rotateCounterClockWise(int restraint) {
	component->rotateCounterClockWise(restraint);
	Block::moveDown(1);
}


bool HeavyBlockDecorator::moveDown(int restraint) {
	//return component->moveDown(n+1);
	return true;
}


void HeavyBlockDecorator::moveLeft() {
	component->moveLeft();
	Block::moveDown(1);
}
*/

void HeavyBlockDecorator::moveRight(int restraint) {
	//component->moveRight(restraint);
	Block::moveDown(1);
}

/*
virtual void rotateClockWise(int restraint);
	virtual void rotateCounterClockWise(int restraint);
	virtual bool moveDown(int restraint);
	virtual void moveLeft();
	virtual void moveRight(int restraint);
	*/