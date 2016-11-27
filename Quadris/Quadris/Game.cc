#include "Game.h"
#include "CommandInterpreter.h"
#include <iostream>
#include <string>
using namespace std;

Game::Game(bool test, int seed, std::string scriptFile, int startLevel): 
	commandIn{CommandInterpreter{cin}}, b{createBoard()} {}

Board Game::createBoard() {
	return Board{};
}

void Game::play() {
	b.generateBlock();
	while (true) {
		cout << b;
		move();
	}
}

void Game::move() {
	string cmd = commandIn.nextInput();
	if (cmd == "left") {
		b.currentBlockLeft();
	} else if (cmd == "right") {
		b.currentBlockRight();
	}
}

void Game::notify(Subject &whoNotified) {

}


