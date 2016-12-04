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
		 std::string filename = "score.txt",
	 	 bool bonus = false);

	void play();
	void notify(Subject &whoNotified);
	SubscriptionType subType() const;


private:
	bool textMode; //Runs Text Only
	TextDisplay display;
	GraphicDisplay gd;
	Board b;
	CommandInterpreter commandIn;

	int highScore;
	int currentScore;
	std::string filename;

	int maxLevel;
	int currentLevel;
	int randSeed;
	std::string scriptFile;
	bool bonus;
	bool DisplayHint;
	bool gameOver;


	void move(); //Uses commandIn to take in a command and then execute the correct Board Function
	void readInHighScore();
	void resetHighScore();
	void updateHighScore();

	void updateScore(int rowsCleared, std::vector<int> lvls);
	Board createBoard();
	void resetBoard();

	void increaseLevel(int n);
	void decreaseLevel(int n);

	void printGameBoard();

};

#endif
