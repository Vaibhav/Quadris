#ifndef COMMAND_INTERPRETER_H
#define COMMAND_INTERPRETER_H

#include <iostream>
#include <map>
#include <vector>

//Handles input and exception safety for that input

//This basically to get input, then game takes that input
//and turns it into a call to Board

class CommandInterpreter {
public:

	//A list of commands
	//Each command is pair composed of a commandCode and a list of the commandCode's arguments
	std::vector < std::pair < std::string, std::vector<std::string> > > nextInput();
	CommandInterpreter(std::istream &, std::ostream &);

private:
	std::istream& in; 
	std::ostream& errorStream;

	//The command dictionary maps a user command as a key and 
	//the programCommand (or an array of program commands) as a value
	//The program command consists of the command itself and an array 
	//of arguments for the program command if it needs it. 
	std::map<std::string, std::vector < std::pair < std::string, std::vector<std::string> > > > commandDictionary;
	void initializeMap(); 
	std::vector < std::pair < std::string, std::vector<std::string> > > findProgramCommands(std::string);
	std::string CommandInterpreter::parseMultiplier(std::string input, std::string& multiplier);
	bool partialMatch(std::string partial, std::string full);

};

#endif

