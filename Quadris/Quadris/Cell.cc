#include "Cell.h"

//Constructor
Cell::Cell (std::shared_ptr <Block> b, char d, int r, int c): blockPtr{b}, displayCharacter{d}, row{r}, col{c} {}

// copy assignment operator
Cell::Cell& operator=( const Cell &other ) {

	if (this == &other) return *this;
	this->row = other.row;
	this->col = other.col;
	this->displayCharacter = other.displayCharacter;
	this->blockPtr = other.blockPtr; 
	other.blockPtr = nullptr; 

}

/*
	if (this == &mx) return *this;
	
	// delete initial matrix array
	for(int i = 0; i < this->numOfRows; i++){
	        delete [] this->mat[i];
	} 

	delete [] this->mat;
	
	int numRows = mx.rows(); 
	int numCols = mx.cols();

	numOfCols = numCols;
	numOfRows = numRows;
	// make new matrix array with same dimensions as mx
	// and copy mx's data
	mat = new int*[numRows];

	for (int i = 0; i < numRows; i++)
	{
    		mat[i] = new int[numCols];
	}
	
	for (int m = 0; m < numRows; m++){
		for(int n = 0; n < numCols; n++){
			mat[m][n] = mx.mat[m][n]; 
	        }
	}

	return *this; 
*/

	
// copy constructor
Cell::Cell ( const Cell &other ): row{other.row}, col{other.col}, displayCharacter{other.displayCharacter} {
	this->blockPtr = other.blockPtr; 
}

/*

numOfRows{mx.numOfRows}, numOfCols{mx.numOfCols} {
	// new matrix array
	this->mat = new int *[this->numOfRows];
	
	// copy elements from mx to this
	for (int i = 0; i < this->numOfRows; i++) {

		this->mat[i] = new int[this->numOfRows];
		
		for (int j = 0; j < this->numOfCols; j++) {
			this->mat[i][j] = mx.mat[i][j];
		}
	}
*/
