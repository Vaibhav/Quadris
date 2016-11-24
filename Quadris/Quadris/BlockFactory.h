#ifndef BLOCKFACTORY_H
#define BLOCKFACTORY_H


class BlockFactory {
public:

	Block generateBlock(int level);

private:
	BlockGenerator generator; 
};

#endif

