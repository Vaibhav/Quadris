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
				
			} else if(commands[i].first == "BLOCK-J"){
				
			} else if(commands[i].first == "BLOCK-L"){
				
			} else if(commands[i].first == "BLOCK-O"){
				
			} else if(commands[i].first == "BLOCK-S"){
				
			} else if(commands[i].first == "BLOCK-Z"){
				
			} else if(commands[i].first == "BLOCK-T"){
				
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


string decrypt_encrypt(string s){

	string encrypted = s;
	char key[3] = {'M', 'V', 'H'};

	for (int i = 0; i < s.size(); i++) {
		encrypted[i] = s[i] ^ key[i % (sizeof(key) / sizeof(char))];
	}

	return s; 

}

void readInHighScore(){

	string temp;
	ifstream file{this->filename};

	// make file contents a string
	getline(file, temp);
	
	// decrypt string
	string hs = decrypt_encrypt(temp);

	// convert string to int and save highscore
	int hScore;
	istringstream(hs) >> hScore;
	this->highscore = hScore;

}

void updateHighScore(){

	ofstream file;
	file.open(this->filename); 

	//convert high score to string
	string hs = to_string(this->highscore);

	//encrypt the highscore
	string toWrite = decrypt_encrypt(hs);

	//write to file 
	file << toWrite;

	file.close();

}

void updateScore(){


}


