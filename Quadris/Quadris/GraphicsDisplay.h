#ifndef __GRAPHICS_DISPLAY_H__
#define __GRAPHICS_DISPLAY_H__

#include "Display.h"
#include <utility>
#include <memory>
#include "window.h"
#include <iostream>

class GraphicDisplay: public Observer {

public:
	Xwindow xw;
	GraphicDisplay(int row=18, int col=11);//, std::unique_ptr<Xwindow>);
	SubscriptionType subType() const override;
	void notify(Subject &whoNotified);
	~GraphicDisplay();

private:
	int sizeOfDisplay;
	int row;
	int col;
	std::vector<std::vector<char>> theBoard; 
};
#endif
