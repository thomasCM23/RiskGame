#include "stdafx.h"
#include "PlayerView.h"
#include <iostream>
#include <iomanip>
using namespace std;

PlayerView::PlayerView() // Constructor
{
};

PlayerView::PlayerView(Player* s) // Constructor with a parameter
{
	_subject = s;
	_subject->attach(this);
};

PlayerView::~PlayerView() // Deconstructor
{
	_subject->detach(this);
};

void PlayerView::update() // Function that will call display()
{
	display();
};

void PlayerView::display() // Function that will display the updated characteristics
{
	vector<Country*> listCountriesOwned = _subject->getListCountriesOwned();
	vector<Continent*> listContinentsOwned = _subject->getListContinentOwned();
	int currentNumberReinforcement = _subject->getReinforcementNumber();
	int totalNumberOfArmies = _subject->getArmiesNumber();
	int numberOfBattlesWon = _subject->getBattlesWon();
	int numberOfBattlesLost = _subject->getBattleLost();
	int totalNumberBattles = numberOfBattlesLost + numberOfBattlesWon;
	int infantryCards = _subject->getInfantryCards();
	int cavalryCards = _subject->getCavalryCards();
	int artilleryCards = _subject->getArtilleryCards();

	cout << "\n========= PLAYER CHARACTERISTICS ===============" << endl;
	cout << "Player " << _subject->getPlayerNumber() << " - " << _subject->getPlayerName() << endl;
	cout << endl;

	cout << "Countries Owned:" << endl;
	for (int i = 0; i < listCountriesOwned.size(); i++)
		cout << listCountriesOwned[i]->getName() << ", ";
	cout << endl;

	cout << "Continent Owned: " << endl;
	for (int i = 0; i < listContinentsOwned.size(); i++)
		cout << listContinentsOwned[i]->getName() << ", ";
	cout << endl;

	cout << "Current Number of Reinforcement: " << currentNumberReinforcement << endl;
	cout << "Total number of armies: " << totalNumberOfArmies << endl;
	cout << "Number of Battles Won: " << numberOfBattlesWon << endl;

	cout << "\n========= PLAYER STATISTICS ===============" << endl;
	cout << "Number of countries owned: " << listCountriesOwned.size() << endl;
	cout << "Number of armies owned: " << totalNumberOfArmies << endl;
	cout << "Number of cards owned: " << (infantryCards + cavalryCards + artilleryCards) << endl;
	cout << "Percentage of the world controlled: " << fixed << setprecision(2) << (listCountriesOwned.size() / 42.0 * 100.0) << "%" << endl;
	if (totalNumberBattles != 0)
	{
		cout << "Percentage of battles won: " << fixed << setprecision(2) << (numberOfBattlesWon / totalNumberBattles * 100.0) << endl;
		cout << "Percentage of battles lost: " << fixed << setprecision(2) << (numberOfBattlesLost / totalNumberBattles * 100.0) << endl;
	}
	
};
