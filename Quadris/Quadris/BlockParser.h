#include <fstream>
#include <string>


class BlockParser {
public:
	BlockParser();
	

private:
	std::string fileLocation; 
	std::ifstream inputFileStream; 


};