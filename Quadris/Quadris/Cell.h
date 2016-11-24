#ifndef CELL_H
#define CELL_H

#include "Subject.h"

class Block;

class Cell {
public:
	Block * blockPtr;
	char displayCharacter;
	int row;
	int col;
public:
	void updateChar(char c); // will notify Board
};

#endif
