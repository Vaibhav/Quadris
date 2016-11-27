#ifndef BOARD_H
#define BOARD_H

#include "Observer.h"
#include "Subject.h"
#include "Block.h"
#include "Cell.h"
#include "Display.h"
#include "BlockFactory.h"
#include <vector>

class Block;
//class Info;

class Board : public Observer, public Subject {
public:
	void currentBlockLeft();
	void currentBlockRight();
	void currentBlockDown();
	void currentBlockUp();
	void currentBlockRotateClockwise();
	void currentBlockRotateCounterClockwise();
	void currentBlockDrop();

	void clearBoard();
	void restart();

	Board(int width=11, int height = 15);
	//void notify(Subject &whoNotified);
	Block generateBlock(); // maybe make a smart pointer

	Cell getInfo() const; // Board is a subject...
	void notify(Subject &whoNotified); // ... and an observer

	friend std::ostream &operator<<(std::ostream &out, const Board&b);

private:
	std::vector< std::vector< Cell > > cells;
	std::vector< Block > blocks;
	Block nextBlock;
	Block currentBlock;

	//Display display;  //Add Graphic display and text display
	BlockFactory blockFactory;

	const int width;
	const int height;

	bool canRotateLeft() const;
	bool canRotateRight() const;
	bool canMoveLeft() const;
	bool canMoveRight() const;
	bool canMoveDown() const;

	void getNextBlock();
	
};


#endif

