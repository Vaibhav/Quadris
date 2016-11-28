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


string decrypt_encrypt(string str) {
    
    char key[6] = {'M', 'V', 'H', 'W', 'K', 'S'}; //Any chars will work, in an array of any size
    string s = str;
    int si = str.size();

    for (int i = 0; i < si; i++)
        s[i] = str[i] ^ key[i % (sizeof(key) / sizeof(char))];
    
    cout << s << endl;
    return s;
}

void readInHighScore(){

	string temp;
	ifstream file{"score.txt"};

	// make file contents a string
	getline(file, temp);
	
	// decrypt string
	string hs = decrypt_encrypt(temp);
	hs = hs.substr(0, hs.size() - 5);
	// convert string to int and save highscore
	int numb;
	istringstream(hs) >> numb;
	cout << "keeping: " << numb << endl;
}

void updateHighScore(){

	ofstream file;
	file.open("score.txt"); 

	//convert high score to string
	string hs = to_string(42);
	hs = hs + "kysvk";
	//encrypt the highscore
	string toWrite = decrypt_encrypt(hs);

	//write to file 
	file << toWrite;
	cout << "writing " << toWrite << endl;
	file.close();

}


