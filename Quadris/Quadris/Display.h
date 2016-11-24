#include "Observor.h"


class Display : Observer {
public:
	void ~Display();
	
private:
	int columnWidth;
	int columnHeight;

};
