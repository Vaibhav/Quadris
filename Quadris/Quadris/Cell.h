#ifndef CELL_H
#define CELL_H

#include "Block.h"

struct Cell {
	Block * blockPtr;

	char displayCharacter;
	int row;
	int col;
};

#endif