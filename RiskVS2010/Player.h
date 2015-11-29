#ifndef PLAYER_H
#define PLAYER_H

#include "stdafx.h"
#include<iostream>
#include <string>
#include <vector>
#include "Country.h"
#include "Continent.h"
#include "Subject.h"

using namespace std;

// Player object
class Player : public Subject
{
public:
	Player(); // Constructor
	Player(string name, int playerNumber); // Constructor with parameters
	~Player(); // Deconstructor
	string getPlayerName(); // Accessor function to get the player name
	void setPlayerName(string name); // Mutator function to set the player name
	int getPlayerNumber(); // Accessor function to get the player number
	void setPlayerNumber(int number); // Mutator function to set the player number

	void addCountryToList(Country* country); // Add a country into the countries list
	void removeCountryFromList(string name); // Remove the country from the list

	void addContinentToList(string name, int bonus); // Add a continent into the continents list
	void removeContinentFromList(string name); // Remove the continent from the continent list

	void updateReinforcementNumber(int armies); // Update the current number of reinforcement

	void addReinforcementNumber(int armies); // Add the number of armies into the total
	void removeReinforcementNumber(int armies); // Remove the number of armies in the total

	void updateBattlesWonNumber(); // Update the number of battles won
	
	vector<Country*> getCountriesThatCanAttack(); // Accessor function to get countries that can attack

	vector<Country*> getListCountriesOwned() { return listCountriesOwned; }; // Accessor function to get the list of countries owned
	vector<Continent*> getListContinentOwned() { return listContinentsOwned; }; // Accessor function to get the list of continent owned
	int getReinforcementNumber() { return currentNumberReinforcement; }; // Accessor function to get the currenct number of reinforcement
	int getArmiesNumber() { return totalNumberOfArmies; }; // Accessor function to get the total number of armies

	void addInfantryCards(int amount); // Add the number of infantry cards into the total
	void addCavalryCards(int amount); // Add the number of cavalry cards into the total
	void addArtilleryCards(int amount); // Add the number of artillery cards into the total

	void removeInfantryCards(int amount); // Remove the number of infantry cards in the total
	void removeCavalryCards(int amount); // Remove the number of cavalry cards in the total
	void removeArtilleryCards(int amount); // Remove the number of artillery cards in the total

	int getTotalNumberCards() { return infantryCards + cavalryCards + artilleryCards; } // Accessor function to get the total number of cards
	int getInfantryCards() { return infantryCards; }; // Accessor function to get the  number of infantry cards
	int getCavalryCards() { return cavalryCards; }; // Accessor function to get the number of  cavalry cards
	int getArtilleryCards() { return artilleryCards; }; // Accessor function to get the number of artillery cards
	int getBonusArmiesFromCards() { return bonusArmiesFromCards; }; // Accessor function to get the number of bonus armies that the player gains from cards
	void incrementBonusArmiesFromCards(); // Function that increment the number of bonus armies from cards

	void addOneWin();
	void addOneLost();

	int getBattlesWon() { return battlesWon; };
	int getBattleLost() { return battlesLost; };

	void setCountriesConqueredThisTurn(int value){ countriesConqueredThisTurn = value; };
	int getCountriesConqueredThisTurn() { return countriesConqueredThisTurn; };

private:
	string name; // Player name
	int playerNumber; // Player number

	vector<Country*> listCountriesOwned; // list containing the countries owned by the player
	vector<Continent*> listContinentsOwned; // list containing the continent owned by the player
	int currentNumberReinforcement; // Current number of reinforcement given
	int totalNumberOfArmies;  // Total number of armies of the player
	int numberOfBattlesWon;	// Total number of battles won

	int infantryCards; // Total number of infantry cards
	int cavalryCards; // Total number of cavalry cards
	int artilleryCards; // Total number of artillery cards
	int bonusArmiesFromCards = 5;

	int battlesWon = 0;
	int battlesLost = 0;
	int countriesConqueredThisTurn = 0;
};
#endif