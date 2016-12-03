#include "Game.h"
#include <sstream>

using namespace std;

const int MAXLEVEL = 4;
const string SCOREFILE = "score.txt";


bool commandLineParser(int argc,
                       char *argv[],
                       bool &text,
                       int &seed,
                       string &scriptFile,
                       int &startLevel,
                       bool &bonus)
{
  for (int i = 1; i < argc; ++i)
  {

    cout << argv[i];
    if (argv[i] == static_cast<string>("-text"))
    {
      text = true;
    }
    else if (argv[i] == static_cast<string>("-seed"))
    {
      if ((i + 1 < argc))
      {
        stringstream s{argv[i + 1]};
        if (s >> seed)
        {
          ++i;
          continue;
        }
      }
      cerr << "Invalid -seed argument";
      return false;
    }
    else if (argv[i] == static_cast<string>("-scriptfile"))
    {
      if ((i + 1 < argc))
      {
        stringstream s{argv[i + 1]};
        if (s >> scriptFile)
        {
          ++i;
          continue;
        }
      }
      cerr << "Invalid -scriptfile argument";
      return false;
    }
    else if (argv[i] == static_cast<string>("-startlevel"))
    {
   //   cout << argv[i] << endl;
      if ((i + 1 < argc))
      {
        stringstream s{argv[i + 1]};
        if (s >> startLevel)
        {
      //    cout << startLevel << endl;
          ++i;
          continue;
        }
      }
      cerr << "Invalid command line argument";
      return false;
    }
    else if (argv[i] == static_cast<string>("-enablebonus")) {
      bonus = true; 
    }
  }
  return true;
}



int main(int argc, char *argv[])
{


  //Game Parameters that can be changed by command line arguments
  bool text = false;
  int seed = 0;
  std::string scriptFile = "sequence.txt";
  int startLevel = 0;
  bool bonus = false;

  if(commandLineParser(argc, argv, text, seed, scriptFile, startLevel, bonus)){
    cout << text << endl;
    cout << seed << endl;
    cout << scriptFile << endl;
    cout << startLevel << endl; //FIX CANT PARSE START LEVEL

  //Create Game
  Game g{MAXLEVEL, text, seed, scriptFile, startLevel, SCOREFILE, bonus};

  //Play Game
  g.play();
  }
}
