#include "Display.h"
#include <utility>
#include <memory>
#include "window.h"
#include <iostream>

class GraphicDisplay: public Observer, public Display {

public:
	GraphicDisplay(int, int, std::unique_ptr<Xwindow>);
	SubscriptionType subType() const override;
	void notify(Subject &whoNotified);

private:
	std::unique_ptr<Xwindow> xw;
	int row;
	int col;

};
