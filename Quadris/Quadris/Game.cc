#include "Game.h"
#include "CommandInterpreter.h"
#include "subscriptions.h"
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <vector>

using namespace std;

Game::Game(int maxLevel, bool test, int seed, std::string scriptFile, int startLevel, string filename = "score.txt"): 
	commandIn { CommandInterpreter{cin, cerr} }, b{ createBoard() } {
	
		this->maxLevel = maxLevel;
		this->currentLevel = startLevel;
		this->b.setLevel(currentLevel);
		this->randSeed = seed;
		this->testMode = test;
		this->scriptFile = scriptFile;
		this->filename = filename;
		this->currentScore = 0;
		this->highscore = 0;
		
		readInHighScore();
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
				cerr << "L" << stoi(commands[i].second[0]);
				b.currentBlockLeft(stoi(commands[i].second[0])); 
			} else if (commands[i].first == "R") {
				cerr << "R" << stoi(commands[i].second[0]);
				b.currentBlockRight(stoi(commands[i].second[0]));
			} else if (commands[i].first == "D") {
				cerr << "D" <<  stoi(commands[i].second[0]);
				b.currentBlockDown(stoi(commands[i].second[0]));
			} else if (commands[i].first == "CW") {
				cerr << "CW" << stoi(commands[i].second[0]);
				b.currentBlockRotateClockwise(stoi(commands[i].second[0]));
			} else if (commands[i].first == "CCW") {
				cerr << "CCW" << stoi(commands[i].second[0]);
				b.currentBlockRotateCounterClockwise(stoi(commands[i].second[0]));
			} else if (commands[i].first == "LU") {
				cerr << "LU" << stoi(commands[i].second[0]);
				increaseLevel(stoi(commands[i].second[0]));
			} else if (commands[i].first == "LD") {
				cerr << "LD" << stoi(commands[i].second[0]);
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
				b.currentBlockDrop();
			} else if(commands[i].first == "RESTART"){
				b.restart();
			} else if(commands[i].first == "HINT"){
				b.showHint();
			} else if(commands[i].first == "RANDOM"){
				b.showHint();
			} else if(commands[i].first == "NORANDOM"){
				b.showHint();
			} else if(commands[i].first == "SEQUENCE"){
				b.showHint();
			} 



			
		}
		cout << display;
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
void readInHighScore(){

	// if file doesnt exists, make the file.
	if (!( file_exists(this->filename) )) {
		fstream file;
		file.open(this->filename, fstream::out);
		file.close();
		this->highscore = 0;
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
	istringstream(hs) >> hScore;
	this->highscore = hScore;

}



void updateHighScore(){

	this->highscore = this->currentScore;
	ofstream file;
	file.open(this->filename); 

	//convert high score to string
	string hs = to_string(this->highscore);
	
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

void updateScore(int rowsCleared, vector<int> lvls) {

	int levelNow = this->currentLevels;
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

	if (this->currentScore > this->highscore) {
		updateHighScore();
	}

}