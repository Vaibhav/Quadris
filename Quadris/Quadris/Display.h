#include "Observer.h"


class Display : public Observer {
public:
	void ~Display();
	
private:
	int columnWidth;
	int columnHeight;

};
