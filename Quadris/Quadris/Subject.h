#ifndef __SUBJECT_H__
#define __SUBJECT_H__

#include "Observer.h"
#include "Cell.h"
#include <vector>
#include <utility>

class Subject {
	
	std::vector< Observer * > observers; //Change to smart pointer
	
public:
	void notifyObservers();
	void attach(Observer *);
	void detach(Observer *);
	virtual Cell getInfo() const = 0;

	virtual ~Subject() = 0;

};
#endif
