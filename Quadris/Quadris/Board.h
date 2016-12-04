#ifndef BOARD_H
#define BOARD_H

#include "Observer.h"
#include "Subject.h"
#include "Block.h"
#include "Cell.h"
#include "Display.h"
#include "GraphicsDisplay.h"
#include "BlockFactory.h"
#include "subscriptions.h"
#include "info.h"
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
	std::pair<int, std::vector<int>> currentBlockDrop();

	void clearBoard();
	void restart();


	Board(TextDisplay *d, GraphicDisplay *gd, std::string sequenceFile = "sequence.txt", int curLevel = 0, int seed = 0, int width=11, int height = 18);

	Block generateBlock(); 

	Info getInfo() const; // Board is a subject...
	void notify(Subject &whoNotified); // ... and an observer
	SubscriptionType subType() const;

	std::vector<int> checkIfRowsComplete();
	std::vector<int> blockLevelsDeleted();

	void setLevel(int n);

	//Sets the current block to the one specified
	//name can be either be
	void setCurrentBlock(std::string name);

	//Hint should be displayed on text by ???
	//and in Graphic Display by a block box
	void showHint();

	void noRandomBlock(std::string file);
	void restoreRandom();
	void setSeed(int seed);
	void setSequence(std::string sequenceFile);
	std::vector<int> clearRows(std::vector<int>);
	std::vector<int> clearRow(int row);
	void printNextBlock();
	void printNextBlockGraphic(GraphicDisplay *gd);


private:
	TextDisplay * display;
	GraphicDisplay *gd;
	BlockFactory blockFactory;
	int currentLevel;

	std::vector< Cell > cells;
	std::vector< Block > blocks;
	Block nextBlock;
	Block currentBlock;

	const int width;
	const int height;

	bool canRotateCW() const;
	bool canRotateCCW() const;
	bool canMoveLeft() const;
	bool canMoveRight(int k=1) const;
	bool canMoveDown() const;
	void getNextBlock();
	void updateScore() const;

	int getLevel(int row, int col, int width); // Gets level from block basically
	void shiftBoardDown(std::vector<int>s);
};


#endif
