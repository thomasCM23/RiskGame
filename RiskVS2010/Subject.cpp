#include "stdafx.h"
#include "Subject.h"
#include "Observer.h"

Subject::Subject() // Constructor
{
	_observers = new list<Observer*>;
}

Subject::~Subject() // Deconstructor
{
	delete _observers;
}

void Subject::attach(Observer* o) // Attach the observer to an observable class
{
	_observers->push_back(o);
};

void Subject::detach(Observer* o) // Dettach the observer
{
	_observers->remove(o);
};

void Subject::notify() // Function that will notify the observers if there is a change
{
	list<Observer *>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)
		(*i)->update();
};