#define COMMAND_INTERPRETER_H

#include <iostream>
#include <map>

//Handles input and exception safety for that input

//This basically to get input, then game takes that input
//and turns it into a call to Board

class CommandInterpreter {
public:

	std::vector< std::string > nextInput();
	CommandInterpreter(std::istream);

private:
	std::istream& in; 
	//The command dictionary maps a user command as a key and 
	//the programCommand (or an array of program commands) as a value
	std::map<std::string, std::vector<std::string> > commandDictionary; 
};

#endif

