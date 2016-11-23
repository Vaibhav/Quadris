#include "Board.h"
#include "CommandInterpreter.h"
#include "Observer"


class Game : Observer {
public:
	Game(bool test = false, int seed, string scriptFile = "sequence.txt", int startLevel = 0);
	Board createBoard();
	void play();

private:
	Board game;
	CommandInterpreter commandIn; 
	int highScore; 
	int currentScore;

	void Move(); //Uses commandIn to take in a command and then execute the correct Board Function 
	void readInHighScore(); 

};