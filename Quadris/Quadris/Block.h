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
	Block(char dispChar,
	 	  std::string colour,
		  std::string name,
		  std::vector < std::pair < int, int > > coords
		  );

	Block();
	~Block();

	//As a single turn in the game, the block moves n times
	void rotateClockWise(int restraint);
	void rotateCounterClockWise(int restraint);
	bool moveDown(int restraint);
	void moveLeft();
	void moveRight(int restraint);
	void setLevel(int n);

	void switchCurrentBlock(std::string blockName);

	void clearRow(int row);
	Info getInfo() const;
	std::string getName();
	std::vector<Cell> getCells() const;
	int getHeight() const;
	int getWidth() const;
	std::pair<int, int> findLowest();
	void clearBlockFromScreen();
	int updateCells(int, int);
	void deleteCells(int, int);

private:
	int size;
	std::string name;
	int level;
	int width;
	int height;
	std::string colour;
	char dispChar;
	std::vector<Cell> prevCells;
	std::vector < std::pair < int, int > > coords;
	std::vector<Cell> cells;
	std::pair<int, int> lowerLeft;

	void rotateUpdate();
	friend std::ostream &operator<<(std::ostream &out, const Block&b);
};

#endif
