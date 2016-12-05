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
#include <memory>
#include <vector>

class Block;
//class BlockFactory;
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

	bool generate();
	void initialize(std::string sequenceFile, int seed);

	Board(TextDisplay *d, GraphicDisplay *gd, 
		std::string sequenceFile = "sequence.txt", int curLevel = 0, 
		int seed = 0, bool textMode=false, int width=11, int height = 18);
 

	Info getInfo() const; // Board is a subject...
	void notify(Subject &whoNotified); // ... and an observer
	SubscriptionType subType() const;

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
	void setHeight(int n);
	void setWidth(int n);

	void printNextBlock();
	void printNextBlockGraphic(GraphicDisplay *gd);
	void addCentreBlock();
	bool wasRowCleared();
	void clearHint();

	void fart() const;
/*
	bool canRotateCW(std::shared_ptr<Block> block) const;
	bool canRotateCCW(std::shared_ptr<Block> block) const;
	bool canMoveLeft(std::shared_ptr<Block> block) const;
	bool canMoveRight(std::shared_ptr<Block> block, int k=1) const;
	bool canMoveDown(std::shared_ptr<Block> block) const;
*/

private:
	TextDisplay * display;
	GraphicDisplay *gd;
	BlockFactory blockFactory;
	int currentLevel;
	bool textMode;

	std::vector< Cell > cells;
	std::vector< std::shared_ptr<Block> > blocks;
	std::shared_ptr<Block> nextBlock;
	std::shared_ptr<Block> currentBlock;
	std::shared_ptr<Block> hintBlock;

	int width;
	int height;

	bool rowCleared; // for centre block

	bool canRotateCW() const;
	bool canRotateCCW() const;
	bool canMoveLeft() const;
	bool canMoveRight(int k=1) const;
	bool canMoveDown() const;
	void getNextBlock();
	void updateScore() const;

	int getLevel(int row, int col, int width); // Gets level from block basically
	void shiftBoardDown(std::vector<int>s);
	std::shared_ptr<Block> generateBlock();
	void attachAndNotify(std::shared_ptr<Block> b);

	std::vector<int> checkIfRowsComplete() const;
	std::vector<int> blockLevelsDeleted() const;

	std::vector<int> clearRows(std::vector<int>);
	std::vector<int> clearRow(int row);

};


#endif
