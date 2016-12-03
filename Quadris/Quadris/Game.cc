#include "Game.h"
#include "CommandInterpreter.h"
#include "subscriptions.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>

using namespace std;


/*
Game::Game(int maxLevel,
		   bool text,
		   int seed,
		   string scriptFile,
		   int startLevel,
		   string scoreFile):
		 commandIn { CommandInterpreter{cin} }, b{ Board{&display, scriptFile, 11, 18}} {
*/
Game::Game(int maxLevel, bool text, int seed, string scriptFile, int startLevel, string filename, bool bonus):
	b{ createBoard() }, commandIn { CommandInterpreter{cin} } {
		this->maxLevel = maxLevel;
		this->currentLevel = startLevel;
		this->b.setLevel(currentLevel);
		this->randSeed = seed;
		this->textMode = text;
		this->scriptFile = scriptFile;
		this->filename = filename;
		this->currentScore = 0;
		this->highScore = 0;
		this->bonus = bonus;
		b.setLevel(currentLevel);
		b.setSeed(seed);

		if (this->bonus) {
			readInHighScore();
		} else {
			resetHighScore();
		}
	}


Board Game::createBoard() {
	return Board{&display, &gd};
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
			if (commands[i].first == "L") {
				//First argument is multiplier, which is by default 1
			//	cerr << "L" << stoi(commands[i].second[0]);
				b.currentBlockLeft(stoi(commands[i].second[0]));
			} else if (commands[i].first == "R") {
		//		cerr << "R" << stoi(commands[i].second[0]);
				b.currentBlockRight(stoi(commands[i].second[0]));
			} else if (commands[i].first == "D") {
		//		cerr << "D" <<  stoi(commands[i].second[0]);
				b.currentBlockDown(stoi(commands[i].second[0]));
			} else if (commands[i].first == "CW") {
		//		cerr << "CW" << stoi(commands[i].second[0]);
				b.currentBlockRotateClockwise(stoi(commands[i].second[0]));
			} else if (commands[i].first == "CCW") {
		//		cerr << "CCW" << stoi(commands[i].second[0]);
				b.currentBlockRotateCounterClockwise(stoi(commands[i].second[0]));
			} else if (commands[i].first == "LU") {
		//		cerr << "LU" << stoi(commands[i].second[0]);
				increaseLevel(stoi(commands[i].second[0]));
			} else if (commands[i].first == "LD") {
		//		cerr << "LD" << stoi(commands[i].second[0]);
				decreaseLevel(stoi(commands[i].second[0]));
			} else if(commands[i].first == "BLOCK-I"){
		//		cerr << "BLOCK-I" << commands[i].second[0];
				b.setCurrentBlock(commands[i].first);
			} else if(commands[i].first == "BLOCK-J"){
		//		cerr << "BLOCK-J" << commands[i].second[0];
				b.setCurrentBlock(commands[i].first);
			} else if(commands[i].first == "BLOCK-L"){
		//		cerr << "BLOCK-L" << commands[i].second[0];
				b.setCurrentBlock(commands[i].first);
			} else if(commands[i].first == "BLOCK-O"){
		//		cerr << "BLOCK-O" << commands[i].second[0];
				b.setCurrentBlock(commands[i].first);
			} else if(commands[i].first == "BLOCK-S"){
		//		cerr << "BLOCK-S" << commands[i].second[0];
				b.setCurrentBlock(commands[i].first);
			} else if(commands[i].first == "BLOCK-Z"){
		//		cerr << "BLOCK-Z" << commands[i].second[0];
				b.setCurrentBlock(commands[i].first);
			} else if(commands[i].first == "BLOCK-T"){
		//	 	cerr << "BLOCK-T" << commands[i].second[0];
				b.setCurrentBlock(commands[i].first);
			} else if(commands[i].first == "DROP"){
		//		cerr << "DROP" << commands[i].second[0];
				std::pair<int, vector<int>> temp;
				temp = b.currentBlockDrop();
				if (temp.first != 0) {
					updateScore(temp.first, temp.second);
				}
			} else if(commands[i].first == "RESTART"){
		//		cerr << "RESTART" << commands[i].second[0];
				b.restart();
			} else if(commands[i].first == "HINT"){
		//		cerr << "HINT" << commands[i].second[0];
				b.showHint();
			} else if(commands[i].first == "RANDOM"){
		//		cerr << "RANDOM";
				int s = commands[i].second.size();
				for(int j = 0; j!= s; ++j){
					cerr <<  commands[i].second[j];
				}
				b.restoreRandom();
			} else if(commands[i].first == "NORANDOM"){
		//		cerr << "NORANDOM" << commands[i].second[0];
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

	while (!lvls.empty()) {
		score += pow((lvls.back() + 1), 2);
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

	// Write to Graphics Display
	gd.xw.drawString(30, 10, "Level: ");// + level);
	gd.xw.drawString(30, 20, "Score: ");
	gd.xw.drawString(30, 30, "Hi Score: ");
	gd.xw.drawString(30, 470, "Next: ");
}
