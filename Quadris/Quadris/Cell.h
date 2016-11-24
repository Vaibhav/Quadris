#ifndef CELL_H
#define CELL_H

class Block;

class Cell {
public:
	Block * blockPtr;

	char displayCharacter;
	int row;
	int col;
};

#endif