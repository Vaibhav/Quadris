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

GraphicDisplay::GraphicDisplay(int row, int col):
row{ row }, col{ col }, sizeOfDisplay{windowSize} {

	int x = sizeOfDisplay/row;
	int y = sizeOfDisplay/col;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			//initially all squares are black
			xw.fillRectangle(i * x, j * y, x, y, Xwindow::White);
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

	int width = sizeOfDisplay / col;
	int height = sizeOfDisplay / row;

	for (auto n:toDelete) {
		int delcoord = width * n.col;
		int delcoord2 = height * n.row;
		this->xw.fillRectangle( delcoord, delcoord2, width, height, Xwindow::White);
	}

	for (auto i:cells) {
		int xcoord = width * i.col;
		int ycoord = height * i.row;

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
