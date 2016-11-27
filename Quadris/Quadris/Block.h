#ifndef BLOCK_H
#define BLOCK_H

#include "Block.h"
#include "Subject.h"
#include "Cell.h"
#include <string>
#include <vector>

class Info;

class Block: public Subject {

public:	
	Block(char dispChar, std::string colour, int level);
	//Block(std::vector<Cell>);
	//Block(const Block&);
	//Block(Block&&);
	//Block& operator=(const Block&);
	//Block& operator=(Block&&);
	Block();
	~Block();

	void rotateClockWise();
	void rotateCounterClockWise();
	void moveDown();
	void moveLeft();
	void moveRight();

	Cell getInfo() const;

private:
	int size;
	int level;
	int width;
	int height;
	std::string colour;
	std::vector<Cell> cells;
	Cell lowerLeft;
	
};

#endif
