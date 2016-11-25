#include "Display.h"
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

Display::~Display(){

}

void Display::notify(Subject &whoNotified) {
	
}

ostream &operator<<(std::ostream &out, const Display&d) {
  for (int i = 0; i < d.height; i++) {
    for (int j = 0; j < d.width; j++) {
      cout << d.theBoard[i][j];
    }
    endl(cout);
  }
}


