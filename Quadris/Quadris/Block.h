#ifndef BLOCK_H
#define BLOCK_H

#include "Block.h"
#include "Subject.h"
#include <string>


class Block : public Subject{

public:	
	Block();
	Block(vector<Cell>);
	Block(const Block&);
	Block(Block&&);
	Block& operator=(const Block&);
	Block& operator=(Block&&);
	~Block();

	void rotateClockWise();
	void rotateCounterClockWise();
	void moveDown();
	void moveLeft();
	void moveRight();

private:
	int size;
	int level;
	std:string color;
	vector<Cell> Cells;
	

}

#endif