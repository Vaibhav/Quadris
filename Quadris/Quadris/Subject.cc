#include "Subject.h"

Subject::~Subject() {
	
}

void Subject::notifyObservers() {
	for (unsigned int i = 0; i < observers.size(); i++) {
		/*if (observers[i]->subType() == t) {
			observers[i]->notify(*this);
		}*/
		observers[i]->notify(*this);
	}
}

