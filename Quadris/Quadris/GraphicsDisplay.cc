#include "GraphicsDisplay.h"
#include "info.h"
#include "Cell.h"
#include "Subject.h"
#include "Block.h"
#include "window.h"
#include <iostream>
#include <memory>
#include <utility>
#include <string>

using namespace std;

const int windowSize = 500;

int GraphicDisplay::calcMarginWidth() {
	return (windowSize - blockSize*col)/2;
}

GraphicDisplay::GraphicDisplay(int row, int col):
 sizeOfDisplay{windowSize}, marginHeight{ 100 }, topMargin {60},
  row{ row }, col{ col }, 
   blockSize{ (windowSize - marginHeight) / row }, 
    marginWidth{ calcMarginWidth() } {

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			//initially all squares are black
			xw.fillRectangle(i * blockSize, j * blockSize, 
				blockSize, blockSize, Xwindow::White);
		}
	}
}		

GraphicDisplay::~GraphicDisplay() {}

SubscriptionType GraphicDisplay::subType() const {
	return SubscriptionType::blockChange; 
}


// {"white", "black", "red", "green", "blue", "cyan", "yellow", "magenta", "orange", "brown"};

void GraphicDisplay::notify(Subject &whoNotified) {

	Info info = whoNotified.getInfo();
	vector <Cell> cells = info.cells;
	vector <Cell> toDelete = info.prevCells;
	string theColor = info.colour;

	int width = blockSize;	// Blocks should be square
	int height = blockSize;

	for (auto n:toDelete) {
		int delcoord = marginWidth + width * n.col;
		int delcoord2 = topMargin + height * n.row;
		this->xw.fillRectangle( delcoord, delcoord2, width, height, Xwindow::White);
	}

	for (auto i:cells) {
		int xcoord = marginWidth + width * i.col;
		int ycoord = topMargin + height * i.row;

		if(theColor == "Red") {
			this->xw.fillRectangle( xcoord , ycoord , width, height, Xwindow::Red);
		} else if (theColor == "Green") {
			this->xw.fillRectangle( xcoord , ycoord , width, height, Xwindow::Green);
		} else if (theColor == "Blue") {
			this->xw.fillRectangle( xcoord , ycoord , width, height, Xwindow::Blue);
		} else if (theColor == "Cyan") {
			this->xw.fillRectangle( xcoord , ycoord , width, height, Xwindow::Cyan);
		} else if (theColor == "Yellow") {
			this->xw.fillRectangle( xcoord , ycoord , width, height, Xwindow::Yellow);
		} else if (theColor == "Orange") {
			this->xw.fillRectangle( xcoord , ycoord , width, height, Xwindow::Orange);
		} else if (theColor == "Magenta") {
			this->xw.fillRectangle( xcoord , ycoord , width, height, Xwindow::Magenta);
		} else if (theColor == "Brown") {
			this->xw.fillRectangle( xcoord , ycoord , width, height, Xwindow::Brown);
		} else if (theColor == "Black") {
			this->xw.fillRectangle( xcoord , ycoord , width, height, Xwindow::Black);
		} else {
			this->xw.fillRectangle( xcoord , ycoord , width, height, Xwindow::White);
		}
	}
}
