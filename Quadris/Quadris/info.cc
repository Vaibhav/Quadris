#include "info.h"

#include <vector>
using namespace std;

Info::Info(vector<Cell> prevCells, vector<Cell> cells, int score): 
	prevCells{prevCells}, cells{cells}, score{score}, moves{0} {}


