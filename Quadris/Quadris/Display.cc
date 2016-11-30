#include "Display.h"
#include "Cell.h"
#include "Subject.h"
#include "subscriptions.h"
#include "info.h"
#include <iostream>
#include <vector>
using namespace std;

Display::Display(int width, int height): width{width}, height{height} {
	for (int i=0; i < height; i++) {
    	theBoard.emplace_back();
    	for (int j=0; j < width; j++) {
      		theBoard[i].emplace_back('*');
    	}
  	}
}

Display::~Display() {}

void Display::notify(Subject &whoNotified) {
  Info info = whoNotified.getInfo();
  vector <Cell> cells = info.cells;
  vector <Cell> toDelete = info.prevCells;
  int j = cells.size();
  for (int i=0; i < j; i++) {
    theBoard[toDelete[i].row][toDelete[i].col] = '*';
  }
  for (int i=0; i < j; i++) {
	 theBoard[cells[i].row][cells[i].col] = cells[i].displayCharacter;
  }
}

SubscriptionType Display::subType() const {
  return SubscriptionType::blockChange;
}

ostream &operator<<(std::ostream &out, const Display&d) {
  for (int i = 0; i < d.height; i++) {
    for (int j = 0; j < d.width; j++) {
      cout << d.theBoard[i][j];
    }
    endl(cout);
  }
  return cout;
}


