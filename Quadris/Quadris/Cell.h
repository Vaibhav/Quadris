#ifndef CELL_H
#define CELL_H
#include <memory>

class Block;

/*
class Cell {
public:
	//Cell(std::shared_ptr <Block>, char, int, int);
	Cell(Block *, char, int, int );
//	Cell& operator=( const Cell & );  // copy assignment operator
//	Cell ( const Cell & );        // copy constructor

	//std::shared_ptr<Block> blockPtr;
	Block * blockPtr;
	char displayCharacter;
	int row;
	int col;

};
*/


struct Cell {

	Cell(Block * blockPointer, char displayCharacter, int row, int col)
	: displayCharacter{displayCharacter}, row{row}, col{col}{
	
	}

	std::shared_ptr<Block> blockPtr;
	char displayCharacter;
	int row;
	int col;
};

#endif
