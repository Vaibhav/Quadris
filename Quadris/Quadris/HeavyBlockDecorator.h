#include <iostream>

/*
Moreover, blocks generated in level 3 are \heavy": every command to
move or rotate the block will be followed immediately and automatically by a downward move
of one row (if possible)
*/

class HeavyBlockDecorator: public BlockDecorator {

public:
	void rotateClockWise(int n) override;
	void rotateCounterClockWise(int n) override;
	void moveDown(int n) override;
	void moveLeft(int n) override;
	void moveRight(int n) override;

}