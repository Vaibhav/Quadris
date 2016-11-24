#include "Observer.h"

class Subject;

class Display : public Observer {
public:
	~Display();
	void notify(Subject &whoNotified);


private:
	int columnWidth;
	int columnHeight;

};
