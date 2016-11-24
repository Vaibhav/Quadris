#ifndef BLOCKFACTORY_H
#define BLOCKFACTORY_H

class BlockGenerator;

class BlockFactory {
public:

	Block generateBlock(int level = 0);
	int setLevel(int newLevel);
	
private:
	BlockGenerator generator;
	int level; 
};

#endif

