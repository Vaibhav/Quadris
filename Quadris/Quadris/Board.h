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
	void currentBlockLeft(int n);
	void currentBlockRight(int n);
	void currentBlockDown(int n);
	void currentBlockRotateClockwise(int n);
	void currentBlockRotateCounterClockwise(int n);
	void currentBlockDrop();

	void clearBoard();
	void restart();

	Board(int width=11, int height = 15);

	Block generateBlock(); // maybe make a smart pointer

	Cell getInfo() const; // Board is a subject...
	void notify(Subject &whoNotified); // ... and an observer

	friend std::ostream &operator<<(std::ostream &out, const Board&b);

	void clearRow(int row);
	std::vector<int> checkIfRowsComplete();

	void setLevel(int n);

private:
	std::vector< std::vector< Cell > > cells;
	std::vector< Block > blocks;
	Block nextBlock;
	Block currentBlock;

	BlockFactory blockFactory;
	int currentLevel;

	const int width;
	const int height;

	bool canRotateLeft() const;
	bool canRotateRight() const;
	bool canMoveLeft() const;
	bool canMoveRight() const;
	bool canMoveDown() const;
	void getNextBlock();
	void updateScore() const;
	
};


#endif

