#include "stdafx.h"
#include "BattlingEntity.h"
#include <stddef.h>

BattlingEntity::BattlingEntity()
{
}

BattlingEntity::BattlingEntity(Player* player, Country* country, Dice dice)
{
	setPlayer(player);
	setDice(dice);
	setCountry(country);
}



BattlingEntity::~BattlingEntity()
{
	delete player;
	player = NULL;
}

Player * BattlingEntity::getPlayer()
{
	return player;
}

void BattlingEntity::setPlayer(Player * ptr)
{
	player = ptr;
}

Dice BattlingEntity::getDice()
{
	return dice;
}

void BattlingEntity::setDice(Dice value)
{
	dice = value;
}

Country * BattlingEntity::getCountry()
{
	return country;
}

void BattlingEntity::setCountry(Country* value)
{
	country = value;
}
