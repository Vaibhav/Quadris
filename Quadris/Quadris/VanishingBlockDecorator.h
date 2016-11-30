#include <iostream>

class VanishingBlockDecorator: public BlockDecorator, Observer {

public:
	void notify(Subject &whoNotified) override;
	SubscriptionType subType() const override;

};
