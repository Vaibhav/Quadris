#ifndef __OBSERVER_H__
#define __OBSERVER_H__

//#include "Subject.h"
class Subject;

class Observer{

public:
	virtual void notify(Subject &whoNotified) = 0;
	virtual ~Observer() = 0;

};

#endif
