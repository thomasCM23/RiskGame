#pragma once
#include <vector>
#include "BattleHelper.h"
using namespace std;

class Dice
{
public:
	Dice();
	~Dice();

	vector<int> getDices();
	void initiateDices(int size, BattleHelper::DiceType diceType);
	void Dice::sort();

	void roll();

private:
	vector<int> dices;
};

