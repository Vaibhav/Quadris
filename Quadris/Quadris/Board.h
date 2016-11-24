#ifndef BOARD_H
#define BOARD_H

#include "Observer.h"
#include "Block.h"
#include "Cell.h"
#include "Display.h"
#include "BlockFactory.h"
#include <vector>

class Board : public Observer {
public:
	void currentBlockLeft();
	void currentBlockRight();
	void currentBlockDown();
	void currentBlockUp();

	void clearBoard();
	

private:
	std::vector< std::vector< Cell > > Cells;
	std::vector< Block > Blocks;
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