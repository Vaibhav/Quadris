#ifndef CELL_H
#define CELL_H

class Block;

struct Cell {
	Block * blockPtr;
	char displayCharacter;
	int row;
	int col;
};

#endif
