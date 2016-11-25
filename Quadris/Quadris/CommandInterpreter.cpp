#include "CommandInterpreter.h"

#include <iostream>

using namespace std;

/*
 left moves the current block one cell to the left. If this is not possible (left edge of the board,
or block in the way), the command has no eect.
 right as above, but to the right.
 down as above, but one cell downward.
 clockwise rotates the block 90 degrees clockwise, as described earlier. If the rotation cannot
be accomplished without coming into contact with existing blocks, the command has no eect.
 counterclockwise as above, but counterclockwise.
 drop drops the current block. It is (in one step) moved downward as far as possible until
it comes into contact with either the bottom of the board or a block. This command also
triggers the next block to appear. Even if a block is already as far down as it can go (as a
result of executing the down command), it still needs to be dropped in order to get the next
block.
 levelup Increases the diculty level of the game by one. The block showing as next still
comes next, but subsequent blocks are generated using the new level. If there is no higher
level, this command has no eect.
 leveldown Decreases the diculty level of the game by one. The block showing as next still
comes next, but subsequent blocks are generated using the new level. If there is no lower
level, this command has no eect.
 norandom file Relevant only during levels 3 and 4, this command makes these levels non-
random, instead taking input from the sequence file, starting from the beginning. This is
to facilitate testing.
 random Relevant only during levels 3 and 4, this command restores randomness in these levels.
 sequence file Executes the sequence of commands found in file. This is to facilitate the
construction of test cases.
 I, J, L, etc. Useful during testing, these commands replace the current undropped block with
the stated block. Heaviness is detemined by the level number. Note that, for heavy blocks,
these commands do not cause a downward move.
 restart Clears the board and starts a new game.
 hint Suggests a landing place for the current block. The game should suggest the best place
to put the current block (spend some time thinking about what \best" might mean), but
it must not suggest a position that is not legally reachable (for example, any postion that
cannot be reached without moving the block upwards). The hint should be indicated on the
text display by a block made of ?'s in the suggest position, and in the graphics display using
the colour black. On the very next command, no matter what the command is, the hint must
disappear from the displays.

*/

CommandInterpreter::CommandInterpreter(const istream &in): in{in} {}

std::string CommandInterpreter::nextInput()
{
	string input;
	cin >> input; // change to in
	
	return input;
}
