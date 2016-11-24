#include "Cell.h"
#include "Info.h"
#include "Subject.h"

void Cell::updateChar(char c) {
	notifyObservers();
	displayCharacter = c;
}

//Info
