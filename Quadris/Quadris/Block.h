#ifndef BLOCK_H
#define BLOCK_H

#include "Block.h"
#include "Subject.h"
#include "Cell.h"
#include "info.h"
#include <string>
#include <vector>

class Info;

class Block: public Subject {

public:	
	//Block(char dispChar, std::string colour, int level);
	Block(char dispChar, 
	 	  std::string colour, 
		  std::string name,
		  std::vector < std::pair < int, int > > coords
		  );
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
	void moveDown(int n, int restraint);
	void moveLeft(int n);
	void moveRight(int n);
	void setLevel(int n);

	void switchCurrentBlock(std::string blockName);

	void clearRow(int row);
	Info getInfo() const;
	std::string getName();
	std::vector<Cell> getCells();
	Cell findLowest();

private:
	int size;
	std::string name;
	int level;
	int width;
	int height;
	std::string colour;
	std::vector<Cell> prevCells;
	std::vector<Cell> cells;
	Cell lowerLeft;
	
};

#endif
