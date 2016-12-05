#ifndef BLOCK_H
#define BLOCK_H

#include "Block.h"
#include "Subject.h"
#include "Cell.h"
#include "info.h"
#include "window.h"
#include "GraphicsDisplay.h"
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
	virtual void rotateClockWise(int restraint);
	virtual void rotateCounterClockWise(int restraint);
	virtual bool moveDown(int restraint);
	virtual void moveLeft();
	virtual void moveRight(int restraint);
	void setLevel(int n);

	void switchCurrentBlock(std::string blockName);

	void clearRow(int row);
	std::pair<int, int> findLowest();
	void clearBlockFromScreen();
	int updateCells(int, int);
	void deleteCells(int, int);
	void moveCellsAboveDown(int row);
	void nextBlockGraphicPls(GraphicDisplay *gd);

	Info getInfo() const;
	std::string getName();
	std::vector<Cell> getCells() const;
	std::vector<Cell> getPrevCells() const;
	int getHeight() const;
	int getWidth() const;
	int getLevel() const;
	std::string getColour() const;
	char getDisplayCharacter() const;
	std::vector < std::pair < int, int > > getCoords() const;
	std::pair<int, int> getLowerLeft() const;

	int getNumberOfMovesInTurn() const; 
	void setNumberOfMovesInTurn(int moves);

protected:
	int size;
	std::string name;
	int level;
	int width;
	int height;
	int numberOfMovesInTurn;
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

