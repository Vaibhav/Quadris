#include "Observer.h"
#include "subscriptions.h"
#include <vector>
#include <iostream>

class Subject;

class Display : public Observer {
public:
	Display(int width=11, int height=15);
	~Display();
	void notify(Subject &whoNotified);
	SubscriptionType subType() const;
	friend std::ostream &operator<<(std::ostream &out, const Display&d);

private:
	int width;
	int height;
	std::vector<std::vector<char>> theBoard;
};
