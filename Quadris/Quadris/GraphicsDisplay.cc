#include "GraphicsDisplay.h"
#include <iostream>
#include <memory>
#include <utility>

using namespace std;

GraphicsDisplay::GraphicDisplay(int row, int col, std::unique_ptr<Xwindow> xw): row{ row }, col{ col }, xw{ xw } {

	this->sizeOfDisplay = 600;

	int x = 600/row;
	int y = 600/col;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			//initially all squares are black
			xw->fillRectangle(i * x, j * y, x, y, Xwindow::White);
		}
	}
}		

GraphicsDisplay::~GraphicDisplay() {}

SubscriptionType GraphicsDisplay::subType() const {
	return SubscriptionType::blockChange; 
}


// {"white", "black", "red", "green", "blue", "cyan", "yellow", "magenta", "orange", "brown"};

void GraphicsDisplay::notify(Subject &whoNotified) {

	Info info = whoNotified.getInfo();
	vector <Cell> cells = info.cells;
	vector <Cell> toDelete = info.prevCells;
	int j = cells.size();

	for (int i = 0; i < j; i++) {
		string theColor = cells[i].blockPtr->colour;

		if(theColor == "Red") {
			this->xw->fillRectangle( sizeOfDisplay / (cells[i].row) , sizeOfDisplay / (cells[i].col) , sizeOfDisplay/row, sizeOfDisplay/col, Xwindow::Red);
		} else if (theColor == "Green") {
			this->xw->fillRectangle( sizeOfDisplay / (cells[i].row) , sizeOfDisplay / (cells[i].col) , sizeOfDisplay/row, sizeOfDisplay/col, Xwindow::Green);
		} else if (theColor == "Blue") {
			this->xw->fillRectangle( sizeOfDisplay / (cells[i].row) , sizeOfDisplay / (cells[i].col) , sizeOfDisplay/row, sizeOfDisplay/col, Xwindow::Blue);
		} else if (theColor == "Cyan") {
			this->xw->fillRectangle( sizeOfDisplay / (cells[i].row) , sizeOfDisplay / (cells[i].col) , sizeOfDisplay/row, sizeOfDisplay/col, Xwindow::Cyan);
		} else if (theColor == "Yellow") {
			this->xw->fillRectangle( sizeOfDisplay / (cells[i].row) , sizeOfDisplay / (cells[i].col) , sizeOfDisplay/row, sizeOfDisplay/col, Xwindow::Yellow);
		} else if (theColor == "Orange") {
			this->xw->fillRectangle( sizeOfDisplay / (cells[i].row) , sizeOfDisplay / (cells[i].col) , sizeOfDisplay/row, sizeOfDisplay/col, Xwindow::Orange);
		} else if (theColor == "Magenta") {
			this->xw->fillRectangle( sizeOfDisplay / (cells[i].row) , sizeOfDisplay / (cells[i].col) , sizeOfDisplay/row, sizeOfDisplay/col, Xwindow::Magenta);
		} else if (theColor == "Brown") {
			this->xw->fillRectangle( sizeOfDisplay / (cells[i].row) , sizeOfDisplay / (cells[i].col) , sizeOfDisplay/row, sizeOfDisplay/col, Xwindow::Brown);
		} else if (theColor == "Black") {
			this->xw->fillRectangle( sizeOfDisplay / (cells[i].row) , sizeOfDisplay / (cells[i].col) , sizeOfDisplay/row, sizeOfDisplay/col, Xwindow::Black);
		} else {
			this->xw->fillRectangle( sizeOfDisplay / (cells[i].row) , sizeOfDisplay / (cells[i].col) , sizeOfDisplay/row, sizeOfDisplay/col, Xwindow::White);
		}
	}

	for (int n = 0; n < j; n++) {
		this->xw->fillRectangle( sizeOfDisplay / (toDelete[n].row), sizeOfDisplay / (toDelete[n].col), sizeOfDisplay/row, sizeOfDisplay/col, Xwindow::White);
	}
}
