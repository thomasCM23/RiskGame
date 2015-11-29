#pragma once
#include "Player.h"
#include "Dice.h"
#include "Country.h"

class BattlingEntity
{
public:
	BattlingEntity();
	BattlingEntity(Player* player, Country* country, Dice dice);
	~BattlingEntity();

	Player* getPlayer();
	void setPlayer(Player* ptr);

	Dice getDice();
	void setDice(Dice value);

	Country* getCountry();
	void setCountry(Country* value);

private:
	Player* player;
	Dice dice;
	Country* country;
};

