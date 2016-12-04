#include <iostream>
#include <memory>
#include "BlockDecorator.h"

/*
Moreover, blocks generated in level 3 are \heavy": every command to
move or rotate the block will be followed immediately and automatically by a downward move
of one row (if possible)
*/

class HeavyBlockDecorator: public BlockDecorator {

public:
	HeavyBlockDecorator(std::shared_ptr<Block> component, int boardHeight);

	void rotateClockWise(int n) override;
	void rotateCounterClockWise(int n) override;
	bool moveDown(int n) override;
	void moveLeft() override;
	void moveRight(int restraint) override;

private:
	bool heavyDown();
	int boardHeight;
	void updateProperties();

};