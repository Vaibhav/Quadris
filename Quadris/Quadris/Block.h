#ifndef BLOCK_H
#define BLOCK_H

#include "Block.h"
#include "Subject.h"
#include <string>


class Block : public Subject{

public:
	
	void rotateClockWise();
	void rotateCounterClockWise();


private:
	int size;
	std:string color;
	vector<Cell> Cells;


}

#endif