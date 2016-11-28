#include "Game.h"
#include "CommandInterpreter.h"
#include "subscriptions.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

Game::Game(int maxLevel, bool test, int seed, std::string scriptFile, int startLevel, string filename = "score.txt"): 
	commandIn { CommandInterpreter{cin, cerr} }, b{createBoard()} {
		this->maxLevel = maxLevel;
		this->currentLevel = startLevel;
		this->b.setLevel(currentLevel);
		this->randSeed = seed;
		this->testMode = test;
		this->scriptFile = scriptFile;
		this->filename = filename;
		// No throw guarantee
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

// Reads in highscore 
void readInHighScore(){

	// if file doesnt exists, throw an exception


	string temp;
	ifstream file{this->highscore};

	// make file contents a string
	getline(file, temp);
	
	// decrypt string
	string hs = decrypt_encrypt(temp);
	hs = hs.substr(0, hs.size() - 5);
	// convert string to int and save highscore
	int hScore;
	istringstream(hs) >> hScore;
	this->highscore = hScore;

}



void updateHighScore(){

	this->highscore = this->score;
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

void updateScore(int rows, vector<int> lvls) {

	if (this->score > this->highscore) {
		updateHighScore();
	}

}