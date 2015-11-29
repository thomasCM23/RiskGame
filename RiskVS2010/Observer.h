#ifndef OBSERVER_H
#define OBSERVER_H

class Observer
{
public:
	~Observer(); // Deconstructor
	virtual void update() = 0; // Pure virtual function
protected:
	Observer(); // Constructor
};

#endif