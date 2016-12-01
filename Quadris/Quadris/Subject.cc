#include "Subject.h"
#include "subscriptions.h"
#include <vector>
#include <iostream>
using namespace std;

Subject::~Subject() {
	
}

void Subject::attach(Observer* o) {
	observers.push_back(o);
	notifyObservers(SubscriptionType::blockChange); // hack
}

void Subject::notifyObservers(SubscriptionType t) {
	cout << "notOb called" << endl;
	for (auto i:observers) {
		if (i->subType() == t) i->notify(*this);
	}
}

