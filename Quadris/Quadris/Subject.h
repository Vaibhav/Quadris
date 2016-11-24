#include "Observer.h"
#include <vector>
#include <utility>

class Subject {
	
	std::vector< Observer * > observers; //Change to smart pointer
	
public:
	void notifyObserver();
	void attach(Observer *);
	void detach(Observer *);

	Subject();

	virtual ~Subject() = 0;

};
