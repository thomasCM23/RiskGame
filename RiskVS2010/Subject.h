#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"
#include <list>

using namespace std;

class Subject
{
public:
	virtual void attach(Observer* o); // Attach the observer to an observable class
	virtual void detach(Observer* o); // Dettach the observer
	virtual void notify(); // Function that will notify the observers if there is a change
	Subject(); // Constructor
	~Subject(); // Deconstructor
private:
	list<Observer*> *_observers;
};

#endif