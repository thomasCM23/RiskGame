#include "stdafx.h"
#include <string>
#include "Player.h"
#include "Country.h"

Player::Player() // Constructor
{
	this->name = "NO NAME";
	this->playerNumber = 0;
}

Player::Player(string name, int playerNumber) // Constructor with parameters
{
	this->name = name;
	this->playerNumber = playerNumber;
}

Player::~Player() // Deconstructor
{
}

string Player::getPlayerName() // Accessor function to get the player name
{
	return this->name;
}

void Player::setPlayerName(string name) // Mutator function to set the player name
{
	this->name = name;
}

int Player::getPlayerNumber() // Accessor function to get the player number
{
	return this->playerNumber;
}

void Player::setPlayerNumber(int number) // Mutator function to set the player number
{
	this->playerNumber = number;
}

void Player::removeCountryFromList(string name) // Remove the country from the list
{
	for (int i = 0; i < this->listCountriesOwned.size(); i++)
		if (this->listCountriesOwned[i]->getName() == name)
			this->listCountriesOwned.erase(this->listCountriesOwned.begin() + i);
	notify();
}

void Player::addCountryToList(Country* country) // Add a country into the countries list
{
	this->listCountriesOwned.push_back(country);
	notify();
}

void Player::addContinentToList(string name, int bonus) // Add a continent into the continents list
{
	this->listContinentsOwned.push_back(new Continent(name, bonus));
	notify();
}

void Player::removeContinentFromList(string name) // Remove the continent from the continent list
{
	for (int i = 0; i < this->listCountriesOwned.size(); i++)
		if (this->listContinentsOwned[i]->getName() == name)
		{
			this->listContinentsOwned.erase(this->listContinentsOwned.begin() + i);
			notify();
		}
			
	
}

void Player::updateReinforcementNumber(int armies)  // Update the current number of reinforcement
{
	this->currentNumberReinforcement = armies;
	this->addReinforcementNumber(armies);
}

void Player::addReinforcementNumber(int armies) // Add the number of armies into the total
{
	this->totalNumberOfArmies += armies;
	notify();
}

void Player::removeReinforcementNumber(int armies) // Remove the number of armies in the total
{
	this->totalNumberOfArmies -= armies;
	notify();
}

void Player::updateBattlesWonNumber() // Update the number of battle won
{
	this->numberOfBattlesWon++;
	notify();
}

void Player::addInfantryCards(int amount)
{
	this->infantryCards += amount;
	notify();
}

void Player::addCavalryCards(int amount)
{
	this->cavalryCards += amount;
	notify();
}

void Player::addArtilleryCards(int amount)
{
	this->artilleryCards += amount;
	notify();
}

void Player::removeInfantryCards(int amount)
{
	this->infantryCards -= amount;
	notify();
}

void Player::removeCavalryCards(int amount)
{
	this->cavalryCards -= amount;
	notify();
}

void Player::removeArtilleryCards(int amount)
{
	this->artilleryCards -= amount;
	notify();
}

void Player::incrementBonusArmiesFromCards()
{
	this->bonusArmiesFromCards += 5;
}

void Player::addOneWin()
{
	this->battlesWon += 1;
	notify();
}

void Player::addOneLost()
{
	this->battlesLost += 1;
	notify();
}

vector<Country*> Player::getCountriesThatCanAttack()
{
	vector<Country*> canAttack;

	for (Country* c : listCountriesOwned)
	{
		if (c->getArmySize() > 2)
			canAttack.push_back(c);
	}

	return canAttack;
}