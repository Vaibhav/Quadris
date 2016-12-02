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
      		theBoard[i].emplace_back(' ');
    	}
  	}
}

Display::~Display() {}

void Display::notify(Subject &whoNotified) {
  Info info = whoNotified.getInfo();
  vector <Cell> cells = info.cells;
  vector <Cell> toDelete = info.prevCells;
  for (auto i:toDelete) {
    theBoard[i.row][i.col] = ' ';
  }
  for (auto i:cells) {
	 theBoard[i.row][i.col] = i.displayCharacter;
  }
}

SubscriptionType Display::subType() const {
  return SubscriptionType::blockChange;
}

ostream &operator<<(std::ostream &out, const Display&d) {
  for (int i = 0; i < d.height; i++) {
    for (int j = 0; j < d.width; j++) {
      out << d.theBoard[i][j];
    }
    endl(out);
  }
  return out;
}


