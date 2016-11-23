#include "Observor.h"
#include <vector>
#include <utility>

class Subject {
	
	std::vector< Observer * > observors; //Change to smart pointer
	
public:
	void notifyObserver();
	void attach(Observer *);
	void detach(Observer *);

	Subject();

	virtual ~Subject() = 0;

};
