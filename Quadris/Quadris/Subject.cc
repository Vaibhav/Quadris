#include "Subject.h"
#include "subscriptions.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

Subject::~Subject() {
	
}

void Subject::attach(Observer* o) {
	observers.push_back(o);
}

void Subject::detach(Observer* o) {
	vector<Observer *>::iterator it = find(observers.begin(), observers.end(), o);
	observers.erase(it);
}


void Subject::notifyObservers(SubscriptionType t) {
	for (auto i:observers) {
		if (i->subType() == t) i->notify(*this);
	}
}

