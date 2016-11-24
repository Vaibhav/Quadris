#ifndef GAME_H
#define GAME_H


#include "Board.h"
#include "CommandInterpreter.h"
#include "Observer.h"
#include <string>


class Game : public Observer {
public:
	Game(bool test = false, int seed = 0, std::string scriptFile = "sequence.txt", int startLevel = 0);
	Board createBoard();
	void play();

private:
	Board game;
	CommandInterpreter commandIn; 
	int highScore; 
	int currentScore;

	void move(); //Uses commandIn to take in a command and then execute the correct Board Function 
	void readInHighScore(); 

};

#endif
