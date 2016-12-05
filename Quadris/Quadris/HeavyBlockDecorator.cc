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

/*
void Board::currentBlockLeft(int n) {
	for (int i=0; i< n; i++) {
		if (!canMoveLeft()) return;
		currentBlock->moveLeft();
	}
}

void Board::currentBlockRight(int n) {
	for (int i=0; i< n; i++) {
		if (!canMoveRight()) return;
		currentBlock->moveRight(width);
	}
}


void Board::currentBlockDown(int n) {
	for (int i=0; i< n; i++) {
		if (!canMoveDown()) return;
		currentBlock->moveDown(height);
	}
}

void Board::currentBlockRotateClockwise(int n) {
	currentBlock->setNumberOfMovesInTurn(n);
	for (int i=0; i< n; i++) {
		if (!canRotateCW()) return;
		currentBlock->rotateClockWise(width);
	}
}


void Board::currentBlockRotateCounterClockwise(int n) {
	currentBlock->setNumberOfMovesInTurn(n);
	for (int i=0; i< n; i++)  {
		if (!canRotateCW()) return;
		currentBlock->rotateCounterClockWise(width);
	}
}

*/

void HeavyBlockDecorator::rotateClockWise(int restraint)
{

    int moves = getNumberOfMovesInTurn();

    for (int i = 0; i < moves; ++i)
    {
	if (!(board->canRotateCW(component)))
	    return;
	component->rotateClockWise(restraint);
	updateProperties();
    }

    if (moves && board->canMoveDown(component))
    {
	component->moveDown(boardHeight);
	updateProperties();
    }

    setNumberOfMovesInTurn(0);
}

void HeavyBlockDecorator::rotateCounterClockWise(int restraint)
{

    int moves = getNumberOfMovesInTurn();

    for (int i = 0; i < moves; ++i)
    {
	if (!(board->canRotateCW(component)))
	    return;
	component->rotateCounterClockWise(restraint);
	updateProperties();
    }

    if (moves && board->canMoveDown(component))
    {
	component->moveDown(boardHeight);
	updateProperties();
    }

    setNumberOfMovesInTurn(0);
}

bool HeavyBlockDecorator::moveDown(int restraint)
{

    int moves = getNumberOfMovesInTurn();

    for (int i = 0; i < moves; ++i)
    {
	if (!(board->canMoveDown(component)))
	    break;
	component->rotateClockWise(restraint);
	updateProperties();
    }
    bool val;
    if (moves && board->canMoveDown(component))
    {
	val = component->moveDown(boardHeight);
	updateProperties();
    }
    else
    {
	val = false;
    }

    setNumberOfMovesInTurn(0);
    return val;
}

void HeavyBlockDecorator::moveLeft()
{

    int moves = getNumberOfMovesInTurn();

    for (int i = 0; i < moves; ++i)
    {
	if (!(board->canMoveLeft(component)))
	    return;
	component->moveLeft();
	updateProperties();
    }

    if (moves && board->canMoveDown(component))
    {
	component->moveDown(boardHeight);
	updateProperties();
    }

    setNumberOfMovesInTurn(0);
}

void HeavyBlockDecorator::moveRight(int restraint) {

	int moves = getNumberOfMovesInTurn();

	  for (int i = 0; i < moves; ++i)
    {
	if (!(board->canMoveRight(component)))
	    return;
	component->moveRight(restraint);
	updateProperties();
    }

    if (moves && board->canMoveDown(component))
    {
	component->moveDown(boardHeight);
	updateProperties();
    }

    setNumberOfMovesInTurn(0);
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


