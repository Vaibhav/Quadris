#ifndef BLOCKFACTORY_H
#define BLOCKFACTORY_H

<<<<<<< HEAD
class BlockGenerator;

class BlockFactory {
public:

	Block generateBlock(int level = 0);
	int setLevel(int newLevel);
	
private:
	BlockGenerator generator;
	int level; 
=======
#include "BlockGenerator.h"
#include "BlockParser.h"

class BlockFactory {
public:
	Block generateBlock(int level = 0);
	int setLevel(int newLevel);

private:
	BlockGenerator * generator; 
	int level;

>>>>>>> 2d5e0dac3ff2eb755507e5a51953e6d934f60e79
};

#endif

