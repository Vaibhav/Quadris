#include "Game.h"
#include "CommandInterpreter.h"
#include "subscriptions.h"
#include "window.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>

using namespace std;

Game::Game(int maxLevel, bool text, int seed, string scriptFile, int startLevel, string scoreFile, bool bonus):
	b{ Board{&display, &gd, scriptFile, startLevel, seed, text, 11, 18} }, commandIn { CommandInterpreter{cin} } {
		this->maxLevel = maxLevel;
		this->currentLevel = startLevel;
		this->b.setLevel(currentLevel);
		this->randSeed = seed;
		this->textMode = text;
		this->scriptFile = scriptFile;
		this->filename = scoreFile;
		this->currentScore = 0;
		this->highScore = 0;
		this->bonus = bonus;
		this->DisplayHint = false;
		this->gameOver = false;
		b.setLevel(currentLevel);
		b.setSeed(seed);

		if (textMode) {
			gd.turnOff();
		}

		if (this->bonus) {
			readInHighScore();
		} else {
			resetHighScore();
		}
	}

void Game::play() {
	while (true) {
		printGameBoard();
		vector < pair<string, vector< string > > > commands;
		try{
		 commands = commandIn.nextInput();
		} catch(out_of_range e){
			cerr << e.what() << endl;
		}
		int numOfCommands = commands.size();
		//Supports Macrocommands, multiple commands which each can have multiple arguments
		for (int i = 0; i != numOfCommands; ++i) {
			if (DisplayHint) {
				b.clearHint(); // Remove hint from display
				DisplayHint = false;
			}

			if (gameOver) {
				if (commands[i].first == "RESTART") {
					resetBoard();
					gameOver = false;
				} else {
					cout << "Game is over" << endl;
					break;
				}
			}

			if (commands[i].first == "L") {
		//First argument is multiplier, which is by default 1
				b.currentBlockLeft(stoi(commands[i].second[0]));
			} else if (commands[i].first == "R") {
				b.currentBlockRight(stoi(commands[i].second[0]));
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
			} else if(commands[i].first == "BLOCK-I"){
				b.setCurrentBlock(commands[i].first);
			} else if(commands[i].first == "BLOCK-J"){
				b.setCurrentBlock(commands[i].first);
			} else if(commands[i].first == "BLOCK-L"){
				b.setCurrentBlock(commands[i].first);
			} else if(commands[i].first == "BLOCK-O"){
				b.setCurrentBlock(commands[i].first);
			} else if(commands[i].first == "BLOCK-S"){
				b.setCurrentBlock(commands[i].first);
			} else if(commands[i].first == "BLOCK-Z"){
				b.setCurrentBlock(commands[i].first);
			} else if(commands[i].first == "BLOCK-T"){
				b.setCurrentBlock(commands[i].first);
			} else if(commands[i].first == "DROP"){
				int times = stoi(commands[i].second[0]);
				std::pair<int, vector<int>> temp;
				for (int i=0; i<times && !gameOver; i++) {
					temp = b.currentBlockDrop();
					if (temp.first != 0) {
						updateScore(temp.first, temp.second);
					}
					if(!b.generate()) gameOver = true;
				}
			} else if(commands[i].first == "RESTART"){
				resetBoard();
			} else if(commands[i].first == "HINT"){
				b.showHint();
				DisplayHint = true;
			} else if(commands[i].first == "RANDOM"){
				int s = commands[i].second.size();
				b.restoreRandom();
			} else if(commands[i].first == "NORANDOM"){
				b.noRandomBlock(commands[i].second[0]);
			} else {
				cout << "programCode is not used" << endl;
			}




		}
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


void Game::notify(Subject &whoNotified) {

}

SubscriptionType Game::subType() const {
	return SubscriptionType::deadBlock; // Used to update score
}


// Encryption function
// Uses XOR encryption to encrypt the highscore before it is saved to text file
// Prevents the user from cheating
string decrypt_encrypt(string str) {

    char key[6] = {'M', 'V', 'H', 'W', 'K', 'S'};
    string s = str;
    int si = str.size();

    for (int i = 0; i < si; i++) {
    	s[i] = str[i] ^ key[i % (sizeof(key) / sizeof(char))];
    }

    return s;
}


// checks if file exists
bool file_exists (const string &fname) {
    ifstream file(fname.c_str());
    return file.good();
}


// Reads in highscore
// 0 is }=1$=8 after encryption.
void Game::readInHighScore(){

	// if file doesnt exists, make the file.
	if (!( file_exists(this->filename) )) {
		fstream file;
		file.open(this->filename, fstream::out);
		file.close();
		this->highScore = 0;
		return;
	}

	string temp;
	ifstream file{this->filename};

	// make file contents a string
	getline(file, temp);
	file.close();

	// decrypt string
	string hs = decrypt_encrypt(temp);
	hs = hs.substr(0, hs.size() - 5);
	// convert string to int and save highscore
	int hScore;
	stringstream ss { hs };
	ss >> hScore; // error handling???
	this->highScore = hScore;

}

void Game::resetHighScore() {
	this->highScore = 0;
	ofstream file;
	file.open(this->filename);

	//convert high score to string
	string hs = to_string(this->highScore);

	//encrypt the highscore
	hs = hs + "kysvk";
	string toWrite = decrypt_encrypt(hs);

	//write to file
	file << toWrite;
	file.close();
}

void Game::updateHighScore(){

	this->highScore = this->currentScore;
	ofstream file;
	file.open(this->filename);

	//convert high score to string
	string hs = to_string(this->highScore);

	//encrypt the highscore
	hs = hs + "kysvk";
	string toWrite = decrypt_encrypt(hs);

	//write to file
	file << toWrite;
	file.close();

}



/*

The game is scored as follows: when a line (or multiple lines) is cleared, you score points equal to
(your current level, plus number of lines) squared.
(For example, clearing a line in level 2 is worth 9 points.)

In addition, when a block is completely removed from the screen (i.e., when all of its cells
have disappeared) you score points equal to the level you were in when the block was generated,
plus one, squared. (For example if you got an O-block while on level 0, and cleared the O-block in
level 3, you get 1 point.)

*/

void Game::updateScore(int rowsCleared, vector<int> lvls) {

	cout<< "The rows cleared: " << rowsCleared << endl;

	int levelNow = this->currentLevel;
	int curScore = this->currentScore;
	int score;

	score = pow((levelNow + rowsCleared), 2);

	// if the vector is empty (no full blocks were cleared)

	if (lvls.empty()) {

		score += curScore;
		this->currentScore = score;
		return;
	}

	int temp;

	while (!lvls.empty()) {
		temp = lvls.back();
		score += pow((temp + 1), 2);
	 	lvls.pop_back();
	}

	score += curScore;
	this->currentScore = score;

	if (this->currentScore > this->highScore) {
		updateHighScore();
	}

}

void printHeader() {
	cout << "-----------" << endl;
}

void Game::printGameBoard() {

	// Print Text Display
	cout << "Level: " << currentLevel << endl;
  	cout << "Score: " << currentScore << endl;
  	cout << "Hi Score: " << highScore << endl;
  	printHeader();
	cout << display;
	printHeader();
	cout << "Next: " << endl;
	b.printNextBlock();
	if (gameOver) cout << "Game over!" << endl;
	if (textMode) return;

	// Clear top/bottom of Graphics Display
	gd.xw.fillRectangle(0,0,110,40,Xwindow::White); // 120 is marginWidth
	gd.xw.fillRectangle(30,420,250,100,Xwindow::White);

	// Write to Graphics Display
	gd.xw.drawString(30, 10, "Level: " + to_string(currentLevel));
	gd.xw.drawString(30, 20, "Score: " + to_string(currentScore));
	gd.xw.drawString(30, 30, "Hi Score: " + to_string(highScore));
	gd.xw.drawString(30, 425, "Next: ");
	b.printNextBlockGraphic(&gd);
	if (gameOver) gd.xw.drawString(30, 480, "Game Over!");
}

void Game::resetBoard() {
	this->currentScore = 0;

	b.restart();
	//Board temp = b; // Deleted when goes out of scope
	b.initialize(scriptFile, randSeed); 
	//= Board{&display, &gd, scriptFile, currentLevel, randSeed};
	printGameBoard();
}
