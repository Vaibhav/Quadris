#ifndef CELL_H
#define CELL_H
#include <memory>

class Block;


class Cell { 
public:
	Cell& operator=( const Cell & );  // copy assignment operator
	Cell ( const Cell & );        // copy constructor
	shared_ptr<Block> blockPtr;
	char displayCharacter;
	int row;
	int col; 

};


/*

struct Cell {
	Block * blockPtr;
	char displayCharacter;
	int row;
	int col;
};

*/

#endif
