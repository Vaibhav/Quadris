#ifndef __DISP_H__
#define __DISP_H__

#include "Observer.h"
#include "subscriptions.h"
#include <vector>
#include <iostream>

class Subject;

class TextDisplay : public Observer {
public:
	TextDisplay(int width=11, int height=18);
	~TextDisplay();
	void notify(Subject &whoNotified);
	SubscriptionType subType() const;
	friend std::ostream &operator<<(std::ostream &out, const TextDisplay&d);

private:
	int width;
	int height;
	std::vector<std::vector<char>> theBoard;
};
#endif
