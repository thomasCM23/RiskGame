#pragma once
#include "BattlingEntity.h"
#include "MapIni.h"
#include "Country.h"
#include "Player.h"
#include <vector>
#include <iostream>
#include <string>

class Battle
{
public:
	Battle();
	Battle(vector<Player*> playersList);
	~Battle();

	void attack(Country* attackingCountry, Country* defendingCountry);
private:
	BattlingEntity attacker;
	BattlingEntity defender;
	vector<Player*> players;

	BattlingEntity getAttacker();
	void setAttacker(BattlingEntity value);

	BattlingEntity getDefender();
	void setDefender(BattlingEntity value);

	Player* getPlayer(string name);
	void executeBattle(BattlingEntity attacker, BattlingEntity defender);
	void captureCountry(BattlingEntity attacker, BattlingEntity defender);

};