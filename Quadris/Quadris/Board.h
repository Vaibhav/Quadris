#ifndef BOARD_H
#define BOARD_H

#include "Observer.h"
#include "Block.h"
#include "Cell.h"
//#include "CellInfo.h"
#include "Display.h"
#include "BlockFactory.h"
#include <vector>
class Block;

class Board { // The board does not need to be an observer
public:
	void currentBlockLeft();
	void currentBlockRight();
	void currentBlockDown();
	void currentBlockUp();
	void currentBlockRotateClockwise();
	void currentBlockRotateCounterClockwise();

	void clearBoard();
	
	Board(Display *display);
	//void notify(Subject &whoNotified);
	Block generateBlock(); // maybe make a smart pointer

private:
	std::vector< std::vector< Cell > > cells;
	std::vector< Block > blocks;
	Block nextBlock;
	Block currentBlock;

	Display * display;  //Add Graphic display and text display
	BlockFactory blockFactory;

	const int width;
	const int length;

	bool canRotateLeft;
	bool canRotateRight;
	bool canMoveLeft;
	bool canMoveRight;
	
};


#endif

