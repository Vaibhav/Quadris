#ifndef GAME_H
#define GAME_H


#include "Board.h"
#include "CommandInterpreter.h"
#include "Observer.h"
#include "subscriptions.h"
#include <string>


class Game : public Observer {
public:
	Game(int maxLevel = 4,
		 bool text = false, 
		 int seed = 0, 
		 std::string scriptFile = "sequence.txt", 
		 int startLevel = 0,
		 std::string filename = "score.txt");

	void play();
	void notify(Subject &whoNotified);
	SubscriptionType subType() const;


private:
	Display display;
	Board b;
	CommandInterpreter commandIn; 
	
	int highScore; 
	int currentScore;
	std::string filename;
	
	int maxLevel;
	int currentLevel;
	bool textMode; //Runs Text Only
	int randSeed;
	std::string scriptFile;


	void move(); //Uses commandIn to take in a command and then execute the correct Board Function 
	void readInHighScore();
	void updateHighScore();

	void updateScore(int rowsCleared, std::vector<int> lvls);
	Board createBoard();
	Board resetBoard();

	void increaseLevel(int n);
	void decreaseLevel(int n);

	void printGameBoard();

};

#endif
