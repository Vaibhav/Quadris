#include "CommandInterpreter.h"

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <fstream>

using namespace std;


std::vector < std::pair < std::string, std::vector<std::string> > >
CommandInterpreter::sequenceCommand(std::string file){
	std::vector < std::pair < std::string, std::vector<std::string> > > commands;
	ifstream fin{file};

	if(!fin.is_open()){
		throw out_of_range("The file could not be opened");
	}

	while(fin){
		std::vector < std::pair < std::string, std::vector<std::string> > > temp = nextInput(fin, 'f');

		//cerr << temp.empty();
		if(!temp.empty()){
		copy(temp.begin(), temp.end(), back_inserter(commands));
		}
	}
	fin.close();
	return commands;

}

std::vector < std::pair < std::string, std::vector<std::string> > > CommandInterpreter::nextInput(){
	return nextInput(this->in, 'i');
}

std::vector<std::pair<std::string, std::vector<std::string>>>
CommandInterpreter::nextInput(istream& in, char inputType)
{
	string input = "";
	getline(in, input);
	stringstream ss{ input };
	string command;
	ss >> command;

	if(command == "" && inputType == 'f'){

		int x;
		in >> x;

		return std::vector<std::pair<std::string, std::vector<std::string>>>();
	}

	string multiplierPrefix;
	command = parseMultiplier(command, multiplierPrefix);

	vector<pair<string, vector<string>>> programCommands;
	try {
		programCommands = findProgramCommands(command);
	}
	catch (std::out_of_range e) {
		throw e;
	}

		vector<string> arguments;

		if( isCommandMultiplierCompatible(programCommands[0].first)
			&& multiplierPrefix != "") {
			arguments.emplace_back(multiplierPrefix);
		}

		string arg;
		while (true) {
			if (!(ss >> arg)) break;
			arguments.emplace_back(arg);
		}

		//ARGUMENTS ARE NOT APPLICABLE WITH MACRO COMMANDS
		if(programCommands.size() == 1){
		//Update one command with arguments
		programCommands[0].second = arguments;
		 }

	//Special Single Commands
	if(programCommands.size() == 1 &&
	   programCommands[0].first == "SEQUENCE"){
	   return sequenceCommand(programCommands[0].second[0]);
	}
		return programCommands;
}

CommandInterpreter::CommandInterpreter(istream &in) : in{ in } {
	initializeMap();
}

bool CommandInterpreter::isCommandMultiplierCompatible(std::string commandName){
	return find(multiplierCompatibleCommands.begin(),
				multiplierCompatibleCommands.end(),
			    commandName) != multiplierCompatibleCommands.end();
}

//Initialize the Map
//ToDo: Initialize Map from file using filestream
//File contains commands next to a list of programCommands
void CommandInterpreter::initializeMap()
{
	vector<string> moveOneUnitArg = vector<string>{ "1" };
	pair<string, vector<string> > PairArg;
	PairArg.second = moveOneUnitArg;

	PairArg.first = "L";
	this->commandDictionary["left"] = vector< pair<string, vector<string> > >{ PairArg };
	PairArg.first = "R";
	this->commandDictionary["right"] = vector< pair<string, vector<string> > >{ PairArg };
	PairArg.first = "D";
	this->commandDictionary["down"] = vector< pair<string, vector<string> > >{ PairArg };
	PairArg.first = "CW";
	this->commandDictionary["clockwise"] = vector< pair<string, vector<string> > >{ PairArg };
	PairArg.first = "CCW";
	this->commandDictionary["counterclockwise"] = vector< pair<string, vector<string> > >{ PairArg };
	PairArg.first = "LU";
	this->commandDictionary["levelup"] = vector< pair<string, vector<string> > >{ PairArg };
	PairArg.first = "LD";
	this->commandDictionary["leveldown"] = vector< pair<string, vector<string> > >{ PairArg };

	//Adding a macro command, probably want a macro command
	//builder helper function to make this easier
	pair<string, vector<string>> FirstCommand;
	FirstCommand.first = "L";
	FirstCommand.second = vector<string>{ "2" };
	pair<string, vector<string>> SecondCommand;
	SecondCommand.first = "D";
	SecondCommand.second = vector<string>{ "1" };
	pair<string, vector<string>> ThirdCommand;
	ThirdCommand.first = "R";
	ThirdCommand.second = vector<string>{ "4" };
	vector< pair<string, vector<string>>> Commands{ FirstCommand, SecondCommand, ThirdCommand };
	//The command is called macro1
	this->commandDictionary["macro1"] = Commands;


	PairArg.first = "DROP";
	PairArg.second = moveOneUnitArg;//vector<string>{ "noArg" };
	this->commandDictionary["drop"] = vector< pair<string, vector<string> > >{ PairArg };
	PairArg.first = "RESTART";
	PairArg.second = vector<string>{ "noArg" };
	this->commandDictionary["restart"] = vector< pair<string, vector<string> > >{ PairArg };
	PairArg.first = "HINT";
	PairArg.second = vector<string>{ "noArg" };
	this->commandDictionary["hint"] = vector< pair<string, vector<string> > >{ PairArg };
	PairArg.first = "RANDOM";
	PairArg.second = vector<string>{ "noArg" };
	this->commandDictionary["random"] = vector< pair<string, vector<string> > >{ PairArg };
	PairArg.first = "NORANDOM";
	PairArg.second = vector<string>{ "norandom" };
	this->commandDictionary["norandom"] = vector< pair<string, vector<string> > >{ PairArg };
	PairArg.first = "SEQUENCE";
	PairArg.second = vector<string>{ "sequence" };
	this->commandDictionary["sequence"] = vector< pair<string, vector<string> > >{ PairArg };

	//TODO: This should be done dynamically depending on the blocks
	//available to the program
	PairArg.second = vector<string>{"noArg"};
	PairArg.first = "BLOCK-I";
	this->commandDictionary["I"] = vector< pair<string, vector<string> > >{ PairArg };
	PairArg.first = "BLOCK-J";
	this->commandDictionary["J"] = vector< pair<string, vector<string> > >{ PairArg };
	PairArg.first = "BLOCK-L";
	this->commandDictionary["L"] = vector< pair<string, vector<string> > >{ PairArg };
	PairArg.first = "BLOCK-O";
	this->commandDictionary["O"] = vector< pair<string, vector<string> > >{ PairArg };
	PairArg.first = "BLOCK-S";
	this->commandDictionary["S"] = vector< pair<string, vector<string> > >{ PairArg };
	PairArg.first = "BLOCK-Z";
	this->commandDictionary["Z"] = vector< pair<string, vector<string> > >{ PairArg };
	PairArg.first = "BLOCK-T";
	this->commandDictionary["T"] = vector< pair<string, vector<string> > >{ PairArg };

	//Adding a macro command, probably want a macro command
	//builder helper function to make this easier
	pair<string, vector<string>> FirstCommand2;
	FirstCommand.first = "DROP";
	FirstCommand.second = vector<string>{ "1" };
	pair<string, vector<string>> SecondCommand2;
	SecondCommand.first = "R";
	SecondCommand.second = vector<string>{ "5" };
	pair<string, vector<string>> ThirdCommand2;
	ThirdCommand.first = "DROP";
	ThirdCommand.second = vector<string>{ "1" };
	vector< pair<string, vector<string>>> Commands2{ FirstCommand2, SecondCommand2, ThirdCommand2 };
	//The command is called bigv
	this->commandDictionary["bigv"] = Commands2;

	////////////////////////////////////////////////////////////
	///Multiplier Compatible Commands Initialization///////////
	multiplierCompatibleCommands = vector<string>{
		"L", "R", "D", "CCW", "CW", "LU", "LD", "DROP"
	};

}

std::vector < std::pair < std::string, std::vector<std::string> > >
CommandInterpreter::findProgramCommands(string userInput)
{
	string key;
	int counter = 0;
	for (std::map<string, std::vector < std::pair < std::string, std::vector<std::string> > > >::const_iterator
		it = commandDictionary.begin(); it != commandDictionary.end(); ++it) {
		if (partialMatch(userInput, it->first)) {
			++counter;
			key = it->first;
		}
	}
	if (counter == 0) {
		throw out_of_range("The command does not exist");
	}
	else if (counter >= 2) {
		throw out_of_range("Ambiguous command call");
	}
	else {
		return commandDictionary[key];
	}
}

string CommandInterpreter::parseMultiplier(string input, string& multiplier) {


	multiplier = "";
	int prefixCounter = 0;
	while (input[prefixCounter] >= '0' &&
		input[prefixCounter] <= '9') {
		multiplier += input[prefixCounter];
		++prefixCounter;
	}

	return input.substr(prefixCounter, input.size() - prefixCounter);
}



bool CommandInterpreter::partialMatch(std::string partial, std::string full)
{
	int strlength = partial.size();
	for (int i = 0; i != strlength; ++i) {
		if (partial[i] != full[i]) return false;
	}
	return true;
}

