#include "VanishingBlockDecorator.h"
#include <iostream>

/*

To allow for some generated blocks to disappear from the screen if not cleared before 10 more blocks have fallen, 
we can decorate Blocks with the property that the block’s cells are deleted from the screen if the condition is met. 
The BlockFactory generates Blocks and adds the decorators. 
A counter will be set in Decorator starting from 10. 
Each time a move is made on the board, the board notifies the block which will call the overridden notify method for the decorated blocks. 
The overridden notify method decrements the counter and if the counter reaches zero, the block deletes all its cells. 
When a row of blocks is cleared, the Board notifies the Block of this event which sets the boolean variable disable to true. 
When disable is true, the block will no longer delete its cells even if this condition is true again after the fact. 

use observer pattern to know when the move occurs. 
notify function. 

*/


void notify(Subject &whoNotified){

	whoNotified.getInfo().moves++;
	int moves = whoNotified.getInfo().moves++;

	if (moves % 10 == 0) { 
		whoNotified.getInfo().moves = 0;

	}

}

SubscriptionType subtype() {
	return SubscriptionType::blockChange; 
}
