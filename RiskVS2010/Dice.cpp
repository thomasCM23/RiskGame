#include "stdafx.h"
#include "Dice.h"
#include "BattleHelper.h"

Dice::Dice()
{
}


Dice::~Dice()
{
}

vector<int> Dice::getDices()
{
	return dices;
}

void Dice::initiateDices(int size, BattleHelper::DiceType diceType)
{
	if (diceType == BattleHelper::attacker && size >= 3) // Attacker has at most 3 Dice
		dices.resize(3);	
	else if (diceType == BattleHelper::defender && size >= 2) // Defender has at most 2 Dice
		dices.resize(2);
	else
	dices.resize(size);
}

void Dice::roll()
{
	for (vector<int>::size_type i = 0; i != dices.size(); i++) 
	{
		dices[i] = (1 + rand() % 6);
	}
}

void Dice::sort()
{
	if (dices.size() == 2)
	{
		if (dices[1] > dices[0])
			swap(dices[1], dices[0]);
	}
	else if (dices.size() == 3)
	{
		if (dices[2] > dices[1])
			swap(dices[2], dices[1]);
		if (dices[2] > dices[0])
			swap(dices[2], dices[0]);
		if (dices[1] > dices[0])
			swap(dices[1], dices[0]);
	}
}

