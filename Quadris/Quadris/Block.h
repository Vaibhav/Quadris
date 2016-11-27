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

	//As a single turn in the game, the block moves n times
	void rotateClockWise(int n);
	void rotateCounterClockWise(int n);
	void moveDown(int n);
	void moveLeft(int n);
	void moveRight(int n);

	void switchCurrentBlock(string blockName);

	void clearRow(int row);
	Cell getInfo() const;

private:
	int size;
	int name;
	int level;
	int width;
	int height;
	std::string colour;
	std::vector<Cell> cells;
	Cell lowerLeft;
	
};

#endif
