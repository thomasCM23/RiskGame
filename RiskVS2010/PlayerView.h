#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H
#include "Player.h"
#include "stdafx.h"
#include <iostream>
#include "Observer.h"

//Concrete observer
class PlayerView : public Observer
{
public:
	PlayerView(); // Constructor
	PlayerView(Player* s); // Constructor with a parameter
	~PlayerView(); // Deconstructor
	void update(); // Function that will call display()
	void display(); // Function that will display the updated characteristics
private:
	Player *_subject;
};

#endif	