#include "HeavyBlockDecorator.h"
#include "Block.h"
#include <iostream>
#include <memory>

using namespace std;

HeavyBlockDecorator::HeavyBlockDecorator(std::shared_ptr<Block> component, int boardHeight, Board * board): 
BlockDecorator{component}, boardHeight{boardHeight}, board{board} {
//cout << endl << "HeavyBlockDecorator Created: " << component->getName() << endl;
updateProperties();
}

void HeavyBlockDecorator::rotateClockWise(int restraint) {
	board->fart();
	component->rotateClockWise(restraint);
	updateProperties();
	component->moveDown(boardHeight);
	updateProperties();
}
	
void HeavyBlockDecorator::rotateCounterClockWise(int restraint) {
	component->rotateCounterClockWise(restraint);
	updateProperties();
	component->moveDown(boardHeight);
	updateProperties();
}


bool HeavyBlockDecorator::moveDown(int restraint) {
bool val = component->moveDown(boardHeight);
updateProperties();
return val;
}


void HeavyBlockDecorator::moveLeft() {
	component->moveLeft();
	updateProperties();
	component->moveDown(boardHeight);
	updateProperties();
}

void HeavyBlockDecorator::moveRight(int restraint) {
	component->moveRight(restraint);
	updateProperties();
	component->moveDown(boardHeight);
	updateProperties();
}

void HeavyBlockDecorator::updateProperties(){
name = component->getName();
colour = component->getColour();
dispChar = component->getDisplayCharacter();
coords = component->getCoords();
this->prevCells = component->getPrevCells();
this->cells = component->getCells();
height = component->getHeight();
width = component->getWidth();
lowerLeft = this->getLowerLeft();
notifyObservers(SubscriptionType::blockChange);
}


