
#include "stdafx.h"
#include "Battle.h"
#include "BattleHelper.h"
#include "MapIni.h"
#include <algorithm>
using namespace std;
Battle::Battle()
{
}

Battle::Battle(vector<Player*> playersList)
{
	players = playersList;
}


Battle::~Battle()
{
}

void Battle::attack(Country* attackingCountry, Country* defendingCountry)
{

	//Initialize Attacker BattlingEntity
	Dice attackerDice;
	attackerDice.initiateDices(attackingCountry->getArmySize(), BattleHelper::attacker);
	BattlingEntity attackerEntity = BattlingEntity(getPlayer(attackingCountry->getOwner()), attackingCountry, attackerDice);

	//Initialize Defender Battling Entity
	Dice defenderDice;
	defenderDice.initiateDices(defendingCountry->getArmySize(), BattleHelper::defender);
	BattlingEntity defenderEntity = BattlingEntity(getPlayer(defendingCountry->getOwner()), defendingCountry, defenderDice);

	// Set BattlingEntities
	setAttacker(attackerEntity);
	setDefender(defenderEntity);

	executeBattle(attackerEntity, defenderEntity);
}

Player * Battle::getPlayer(string name)
{
	for (Player* pl : players)
	{
		if (pl->getPlayerName() == name)
			return pl;
	}
	return NULL;
}


BattlingEntity Battle::getAttacker()
{
	return attacker;
}

void Battle::setAttacker(BattlingEntity value)
{
	attacker = value;
}

BattlingEntity Battle::getDefender()
{
	return defender;
}

void Battle::setDefender(BattlingEntity value)
{
	defender = value;
}


void Battle::executeBattle(BattlingEntity attacker, BattlingEntity defender)
{
	// Roll and Sort Dices
	attacker.getDice().roll();
	attacker.getDice().sort();

	defender.getDice().roll();
	defender.getDice().sort();

	//Display
	cout << endl << "Attacker rolled: " << (attacker.getDice()).getDices()[0] << "  ";
	if ((attacker.getDice()).getDices().size() > 1)
		cout << (attacker.getDice()).getDices()[1] << "  ";
	if ((attacker.getDice()).getDices().size() > 2)
		cout << (attacker.getDice()).getDices()[2] << "  ";
	cout << endl << "Defender rolled: " << (defender.getDice()).getDices()[0] << "  ";
	if ((defender.getDice()).getDices().size() > 1)
		cout << (defender.getDice()).getDices()[1] << endl;

	int attackerCurrentDie;
	int defenderCurrentDie;

	// Compare First Dice
	attackerCurrentDie = (attacker.getDice()).getDices()[0];
	defenderCurrentDie = (defender.getDice()).getDices()[0];

	if (defenderCurrentDie >= attackerCurrentDie)
		attacker.getCountry()->removeArmies(1);
	else
		defender.getCountry()->removeArmies(1);

	//Compare Second Dice
	attackerCurrentDie = (attacker.getDice().getDices().size() > 1) ? (attacker.getDice()).getDices()[1] : 0;
	defenderCurrentDie = (defender.getDice().getDices().size() > 1) ? (defender.getDice()).getDices()[1] : 0;

	if (defenderCurrentDie >= attackerCurrentDie)
		attacker.getCountry()->removeArmies(1);
	else
		defender.getCountry()->removeArmies(1);

	//Compare Third Dice
	attackerCurrentDie = (attacker.getDice().getDices().size() > 2) ? (attacker.getDice()).getDices()[2] : 0;
	defenderCurrentDie = (defender.getDice().getDices().size() > 2) ? (defender.getDice()).getDices()[2] : 0;

	if (defenderCurrentDie >= attackerCurrentDie)
		attacker.getCountry()->removeArmies(1);
	else
		defender.getCountry()->removeArmies(1);


	// Battle is over: Assess Results
	if (defender.getCountry()->getArmySize() == 0 &&
		attacker.getCountry()->getArmySize() > attacker.getDice().getDices().size())
		captureCountry(attacker, defender);
	// empty attacking country??

}

void Battle::captureCountry(BattlingEntity attacker, BattlingEntity defender)
{
	bool validInput = false;
	int armiesToMove;

	while (!validInput)
	{
		cout << "Defender has no more armies in Country. Capturing Country. Attacker may move between " << attacker.getDice().getDices().size() <<
			" and " << attacker.getCountry()->getArmySize() - 1 << endl; //Must keep at least one army in his country
		cout << "Must keep at least one army in your country." << endl;
		cout << "Move How many Armies?" << endl;
		 
		cin >> armiesToMove;
		validInput = (armiesToMove >= attacker.getDice().getDices().size() && armiesToMove <= attacker.getCountry()->getArmySize()-1);
	}

	// Defender loses Country
	(defender.getPlayer())->removeCountryFromList(defender.getCountry()->getName());
	(attacker.getPlayer())->addCountryToList(defender.getCountry());  

	// Assign Country to new Owner
	defender.getCountry()->setOwner(defender.getPlayer()->getPlayerName());

	// Move Armies to new Country
	defender.getCountry()->addArmies(armiesToMove);
	attacker.getCountry()->removeArmies(armiesToMove);

	(attacker.getPlayer())->setCountriesConqueredThisTurn((attacker.getPlayer())->getCountriesConqueredThisTurn() + 1);
}
