#include <iostream>


//Handles input and exception safety for that input

//This basically to get input, then game takes that input
//and turns it into a call to Board

class CommandInterpreter {
public:

	std::string nextInput();
	CommandInterpreter(std::istream);


private:
	std::istream& in; 


};