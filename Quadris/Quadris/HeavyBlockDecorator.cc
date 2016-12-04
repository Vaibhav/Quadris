#include "HeavyBlockDecorator.h"
#include "Block.h"
#include <iostream>
#include <memory>

using namespace std;

HeavyBlockDecorator::HeavyBlockDecorator(std::shared_ptr<Block> component, int boardHeight): 
BlockDecorator{component}, boardHeight{boardHeight}{
cout << endl << "HeavyBlockDecorator Created: " << component->getName() << endl;
updateProperties();
}

void HeavyBlockDecorator::rotateClockWise(int restraint) {
	cout << endl << "HEAVY BLOCK MOVE: " << component->getName() << endl;

	component->moveDown(boardHeight);
	updateProperties();
	component->rotateClockWise(restraint);
	updateProperties();

}
	
void HeavyBlockDecorator::rotateCounterClockWise(int restraint) {
	cout << endl << "HEAVY BLOCK MOVE: " << component->getName() << endl;

	component->moveDown(boardHeight);
	updateProperties();
	component->rotateCounterClockWise(restraint);
	updateProperties();
}

/*
bool HeavyBlockDecorator::heavyDown(){
bool val = component->moveDown(this->height);
if(val == false) return false;
prevCells = component->getPrevCells();
cells = component->getCells();
lowerLeft = component->getLowerLeft();
notifyObservers(SubscriptionType::blockChange);
return true;
}
*/

bool HeavyBlockDecorator::moveDown(int restraint) {
//if(heavyDown() == false) return false;
//return heavyDown();
bool val = component->moveDown(boardHeight);
updateProperties();
return val;

}


void HeavyBlockDecorator::moveLeft() {
	cout << endl << "HEAVY BLOCK MOVE: " << component->getName() << endl;
	component->moveLeft();
	updateProperties();
	component->moveDown(boardHeight);
	updateProperties();
}

void HeavyBlockDecorator::moveRight(int restraint) {
	cout << endl << "HEAVY BLOCK MOVE: " << component->getName() << endl;
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



/*

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


	
	
	*/