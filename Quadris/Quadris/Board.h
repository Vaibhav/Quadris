#include "Observor.h"
#include "Block.h"
#include "CellInfo.h"
#include "Display.h"

#include <vector>

class Board : public Observer {
public:
	Board






private:
	std::vector< std::vector<CellInfo> > Cells;
	std::vector< Block > Blocks; 
	Display * display;  //Add Graphic display and text display 
};