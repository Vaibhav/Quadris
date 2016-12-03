#ifndef __INFO_H__
#define __INFO_H__

#include <vector>
#include <string>
#include "Cell.h"

class Info {
public:
	Info(std::vector<Cell> prevCells, 
		std::vector<Cell> cells, int score=-1, std::string colour="empty");
	std::vector<Cell> prevCells;
	std::vector<Cell> cells;
	int score;
	int moves;
	std::string colour;
};

#endif
