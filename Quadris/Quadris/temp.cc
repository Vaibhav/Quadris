#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

string decrypt_encrypt(string toEncrypt) {
    
    char key[6] = {'M', 'V', 'H', 'W', 'K', 'S'}; //Any chars will work, in an array of any size
    string s = toEncrypt;
    int si = toEncrypt.size();

    for (int i = 0; i < si; i++)
        s[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];
    
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

int main(){
    updateHighScore();
    readInHighScore();
}

