#include "GraphicsDisplay.h"
#include <iostream>
#include <memory>
#include <utility>

using namespace std;

GraphicDisplay(int row, int col, std::unique_ptr<Xwindow> xw): row{ row }, col{ col }, xw{ xw } {}		

SubscriptionType subType() const {
	return SubscriptionType::blockChange; 
}

void notify(Subject &whoNotified) {
	
}
