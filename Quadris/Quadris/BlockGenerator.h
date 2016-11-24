
#include "BlockParser.h"


class BlockGenerator {
	
	virtual Block generateBlock() = 0;
	int setLevel(int newLevel);


private:
	BlockParser blockParser; 
	int level;



};
