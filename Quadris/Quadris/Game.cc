#include "Game.h"
#include "CommandInterpreter.h"
#include <iostream>
#include <string>

using namespace std;

Game::Game(int maxLevel, bool test, int seed, std::string scriptFile, int startLevel): 
	commandIn { CommandInterpreter{cin, cerr} }, b{createBoard()} {
		this->maxLevel = maxLevel;
		this->currentLevel = startLevel;
		this->b.setLevel(currentLevel);
		this->randSeed = seed;
		this->testMode = test;
		this->scriptFile = scriptFile;
	}

Board Game::createBoard() {
	return Board{};
}

void Game::play() {
	while (true) {
		vector < pair<string, vector< string > > > commands;
		try{
		 commands = commandIn.nextInput();
		} catch(out_of_range e){
			cerr << e.what() << endl;
		}
		int numOfCommands = commands.size();
		//Supports Macrocommands, multiple commands which each can have multiple arguments
		for (int i = 0; i != numOfCommands; ++i) {
			if (commands[i].first == "L") {
				//First argument is multiplier, which is by default 1
				b.currentBlockLeft(stoi(commands[i].second[0])); 
			} else if (commands[i].first == "R") {
				b.currentBlockRight(stoi(commands[i].second[0]));
			} else if (commands[i].first == "L") {
				b.currentBlockLeft(stoi(commands[i].second[0]));
			} else if (commands[i].first == "D") {
				b.currentBlockDown(stoi(commands[i].second[0]));
			} else if (commands[i].first == "CW") {
				b.currentBlockRotateClockwise(stoi(commands[i].second[0]));
			} else if (commands[i].first == "CCW") {
				b.currentBlockRotateCounterClockwise(stoi(commands[i].second[0]));
			} else if (commands[i].first == "LU") {
				increaseLevel(stoi(commands[i].second[0]));
			} else if (commands[i].first == "LD") {
				decreaseLevel(stoi(commands[i].second[0]));
			}
		}
		cout << b;
		//move();
	}
}

void Game::increaseLevel(int n){
	if((currentLevel + n) >= maxLevel){
		currentLevel = maxLevel;
	} else{
		currentLevel += n;
	}
	b.setLevel(currentLevel);
}

void Game::decreaseLevel(int n){
	if((currentLevel - n) <= 0){
		currentLevel = 0;
	} else{
		currentLevel -=n;
	}
	b.setLevel(currentLevel);
}

/*
void Game::move() {
	string cmd = "left"; //hardcoded
	if (cmd == "left") {
		b.currentBlockLeft(1);
	} else if (cmd == "right") {
		b.currentBlockRight(1);
	}
}
*/
void Game::notify(Subject &whoNotified) {

}

