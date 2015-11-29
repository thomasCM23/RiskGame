#include <iostream>
#include "stdafx.h"
#include "MainPhase.h"
#include "Player.h"
#include "Country.h"
#include "World.h"
using namespace std;

MainPhase::MainPhase() // Constructor
{
}

void MainPhase::reinforce(Player* player)
{
	//Reset the number of countries conquered this turn to 0.
	player->setCountriesConqueredThisTurn(0);
	continentsChecking(player);

	cout << "Player " << player->getPlayerNumber() << ": " << player->getPlayerName() << " -> Reinforcing countries !" << endl;

	int numberOfArmiesToReceive;
	vector<Country*> vectorCountries = player->getListCountriesOwned();
	vector<Continent*> vectorContinent = player->getListContinentOwned();

	if (floor(vectorCountries.size() / 3) < 3)
		numberOfArmiesToReceive = 3;
	else
		numberOfArmiesToReceive = floor(vectorCountries.size() / 3.0);

	for (int i = 0; i < vectorContinent.size(); i++)
	{
		if (vectorContinent[i]->getName() == "Asia")
			numberOfArmiesToReceive += 7;
		if (vectorContinent[i]->getName() == "North America")
			numberOfArmiesToReceive += 5;
		if (vectorContinent[i]->getName() == "Europe")
			numberOfArmiesToReceive += 5;
		if (vectorContinent[i]->getName() == "Africa")
			numberOfArmiesToReceive += 3;
		if (vectorContinent[i]->getName() == "Australia")
			numberOfArmiesToReceive += 2;
		if (vectorContinent[i]->getName() == "South America")
			numberOfArmiesToReceive += 2;
	}

	bool validInput = false;
	bool enoughForExchange = false;
	bool confirmationExchange = false;

	if (player->getTotalNumberCards() >= 5)
	{
		cout << "\nYour total amount of cards is greater or equal to 5 cards, You will automatically exchange your cards for bonus armies !\n" << endl;
		if (player->getInfantryCards() >= 1 && player->getCavalryCards() >= 1 && player->getArtilleryCards() >= 1)
		{
			numberOfArmiesToReceive += player->getBonusArmiesFromCards();
			cardsOneOfEach(player);
		}

		if (player->getInfantryCards() >= 3 || player->getCavalryCards() >= 3 || player->getArtilleryCards() >= 3)
		{
			numberOfArmiesToReceive += player->getBonusArmiesFromCards();
			cardsThreeSame(player);
		}
	}

	if ((player->getInfantryCards() >= 1 && player->getCavalryCards() >= 1 && player->getArtilleryCards() >= 1) ||
		(player->getInfantryCards() >= 3 || player->getCavalryCards() >= 3 || player->getArtilleryCards() >= 3))
		enoughForExchange = true;

	if (enoughForExchange)
	{
		while (!validInput)
		{
			char exchangeConfirmation;
			cin.clear();
			cout << "Would you like to exchange your cards (3 of the same type or 1 of each) for additionnal armies? 'Y/y' for yes or 'N/n' for no: ";
			cin >> exchangeConfirmation;

			if (exchangeConfirmation == 'Y' || exchangeConfirmation == 'y')
			{
				confirmationExchange = true;
				validInput = true;
			}
			else if (exchangeConfirmation == 'N' || exchangeConfirmation == 'n')
				validInput = true;
		}

		if (confirmationExchange)
		{
			if (player->getInfantryCards() >= 1 && player->getCavalryCards() >= 1 && player->getArtilleryCards() >= 1)
			{
				numberOfArmiesToReceive += player->getBonusArmiesFromCards();
				cardsOneOfEach(player);
			}

			if (player->getInfantryCards() >= 3 || player->getCavalryCards() >= 3 || player->getArtilleryCards() >= 3)
			{
				numberOfArmiesToReceive += player->getBonusArmiesFromCards();
				cardsThreeSame(player);
			}
		}
	}

	player->updateReinforcementNumber(numberOfArmiesToReceive);
	this->putArmiesInCountries(player);
}

void MainPhase::attack(Player* attacker, map<string, Country*> allCountries, vector<Player*> players) // Stub function - Attack phase                   !!!!!!!!!!!! implements the battle part of Marie in here
{
	bool moreAttacks = false;
	bool validAttackSymbol = false;

	while (!validAttackSymbol) {
		char attackConfirmation;
		cin.clear();
		cout << "Would you like to issue an attack? 'Y/y' for yes or 'N/n' for no: ";
		cin >> attackConfirmation;

		if (attackConfirmation == 'Y' || attackConfirmation == 'y')
		{
			moreAttacks = true;
			validAttackSymbol = true;
		}
		else if (attackConfirmation == 'N' || attackConfirmation == 'n')
			validAttackSymbol = true;
	}


	// While loop, if the player wants to issue more attacks
	while (moreAttacks)
	{

		cout << "Here is the list of countries that can attack: " << endl;
		for (Country * c : attacker->getCountriesThatCanAttack())
		{
			cout << "- " << c->getName() << ": " << c->getArmySize() << " armies" << endl;
		}

		Country* attackingCountry = NULL;

		while (attackingCountry == NULL)
		{
			string attackerCountryName;
			cout << "Enter the name of the country you want to use to attack: ";
			cin >> attackerCountryName;

			vector<Country*> attackerList = attacker->getCountriesThatCanAttack();
			for (Country* c : attackerList)
			{
				if (c->getName() == attackerCountryName)
				{
					attackingCountry = c;
					break;
				}
			}
		}

		Country* defendingCountry = NULL;

		while (defendingCountry == NULL)
		{
			string defenderCountryName;
			cout << "What country you want to attack? Enter the country name: ";
			cin >> defenderCountryName;

			for (map<string, Country*>::iterator it = allCountries.begin(); it != allCountries.end(); ++it)
			{
				if (it->second->getName() == defenderCountryName)
				{
					defendingCountry = it->second;
					break;
				}
			}

		}
		char moreAttacksConfirmation;
		bool isWrongAnswer = true;


		Battle battle;
		battle.attack(attackingCountry, defendingCountry);

		if (attacker->getCountriesConqueredThisTurn() == 1)
		{
			int cardNumber = (1 + rand() % 3);
			switch (cardNumber)
			{
			case(1) :
				attacker->addInfantryCards(1);
				break;
			case(2) :
				attacker->addCavalryCards(1);
				break;
			case(3) :
				attacker->addArtilleryCards(1);
				break;
			}
		}

		Player* defendingPlayer = NULL;
		for (Player* p : players)
		{
			if (p->getPlayerName() == defendingCountry->getOwner())
			{
				defendingPlayer = p;
				break;
			}
		}

		if (defendingPlayer != NULL)
		{
			cout << "Player " << defendingPlayer->getPlayerName() << " has lost. Will be removed from the game." << endl;
			cout << " All of his/her cards will be transferred to: " << attacker->getPlayerName() << endl;

			if (defendingPlayer->getListCountriesOwned().size() == 0)
			{
				attacker->addInfantryCards(defendingPlayer->getInfantryCards());
				attacker->addArtilleryCards(defendingPlayer->getArtilleryCards());
				attacker->addCavalryCards(defendingPlayer->getCavalryCards());
			}
			//remove player from the game
			players.erase(players.begin() + defendingPlayer->getPlayerNumber() - 1);

		}


		// While loop, confirmation for more attacks
		while (isWrongAnswer)
		{
			cout << "\nWould you like to attack another country?\nEnter 'Y/y' for yes or 'N/n' for no: ";
			cin >> moreAttacksConfirmation;
			if (moreAttacksConfirmation == 'N' || moreAttacksConfirmation == 'n')
			{
				moreAttacks = false;
				isWrongAnswer = false;
			}
			else
				if (moreAttacksConfirmation == 'Y' || moreAttacksConfirmation == 'y')
				{
					moreAttacks = true;
					isWrongAnswer = false;
				}
				else
				{
					cout << "Wrong answer" << endl;
					isWrongAnswer = true;
				}
		}
	}
}

void MainPhase::fortification(Player* player, World* world) // Stub function - Fortification phase
{
	cout << "Player " << player->getPlayerNumber() << ": " << player->getPlayerName() << " -> Fortifying countries !" << endl;
	moveArmies(player, world);

}

void MainPhase::cardsOneOfEach(Player* player)
{
	player->incrementBonusArmiesFromCards();
	player->removeInfantryCards(1);
	player->removeCavalryCards(1);
	player->removeArtilleryCards(1);
}

void MainPhase::cardsThreeSame(Player* player)
{
	player->incrementBonusArmiesFromCards();

	if (player->getInfantryCards() >= 3)
		player->removeInfantryCards(3);
	else if (player->getCavalryCards() >= 3)
		player->removeCavalryCards(3);
	else if (player->getArtilleryCards() >= 3)
		player->removeArtilleryCards(3);
}

void MainPhase::putArmiesInCountries(Player* player)
{
	string reinforceConfirmation;
	string destinationCountry;
	int numberOfArmies;
	vector<Country*> vectorCountries = player->getListCountriesOwned();
	string doneConfirmation;
	bool done = false;
	bool validInput = false;

	while (!validInput) {
		cin.clear();
		cout << "\nDo you want to reinforce your countries? 'y' for yes, 'n' for no: ";
		cin >> reinforceConfirmation;

		if (reinforceConfirmation == "Y" || reinforceConfirmation == "y")
			validInput = true;
		else if (reinforceConfirmation == "N" || reinforceConfirmation == "n")
			validInput = true;
	}

	if (reinforceConfirmation == "y")
		while (!done)
		{
			cout << endl;

			for (int i = 0; i < player->getListCountriesOwned().size(); i++)
				cout << vectorCountries[i]->getName() << " (" << vectorCountries[i]->getArmySize() << "), ";

			cout << endl;

			bool validCountry = false;

			while (!validCountry)
			{
				cout << "\nWhere do you want to put your armies? ";
				getline(cin, destinationCountry);

				for (Country* c : player->getListCountriesOwned())
				{
					if (c->getName() == destinationCountry)
					{
						validCountry = true;
						break;
					}
				}
			}

			cout << "\nYou have a total of " << player->getArmiesNumber() << " armies to place." << endl;
			cout << "\nHow many armies you want to put in " << destinationCountry << " ? ";
			cin >> numberOfArmies;
			while (!cin || numberOfArmies > player->getArmiesNumber()) {
				cout << "\nHow many armies you want to put in " << destinationCountry << " ? ";
				cin.clear();
				cin.ignore(256, '\n');
				cin >> numberOfArmies;
			}

			for (int i = 0; i < vectorCountries.size(); i++)
				if (vectorCountries[i]->getName() == destinationCountry)
				{
					vectorCountries[i]->addArmies(numberOfArmies);
					player->removeReinforcementNumber(numberOfArmies);
					break;
				}


			if (player->getArmiesNumber() > 0)
			{
				bool validInput = false;
				while (!validInput) {
					cin.clear();
					cout << "\nWould you like to reinforce your other countries? 'y' for yes, 'n' for no: ";
					cin >> doneConfirmation;

					if (doneConfirmation == "Y" || doneConfirmation == "y")
						validInput = true;
					else if (doneConfirmation == "N" || doneConfirmation == "n")
					{
						validInput = true;
						done = true;
					}
				}
			}
			else
			{
				cout << "You have no more armies to place." << endl;
				done = true;
			}
		}
}

void MainPhase::moveArmies(Player* player, World* world)
{
	string fortifyConfirmation;
	string doneConfirmation;
	string fromCountry;
	string destinationCountry;
	int numberOfArmies;
	vector<Country*> vectorCountries = player->getListCountriesOwned();
	Country* c = NULL;
	bool done = false;
	bool fortify = false;

	bool validInput = false;

	while (!validInput) {
		cin.clear();
		cout << "\nDo you want to fortify your countries? 'y' for yes, 'n' for no: ";
		cin >> fortifyConfirmation;

		if (fortifyConfirmation == "Y" || fortifyConfirmation == "y")
		{
			fortify = true;
			validInput = true;
		}
		else if (fortifyConfirmation == "N" || fortifyConfirmation == "n")
		{
			fortify = false;
			validInput = true;
		}
	}

	if (fortify)
		cout << endl;

	cout << "Your countries: " << endl;
	for (int i = 0; i < player->getListCountriesOwned().size(); i++)
		cout << vectorCountries[i]->getName() << " (" << vectorCountries[i]->getArmySize() << "), ";

	cout << "\n\nPossible destination countries are " << endl;
	cout << endl;

	for (int i = 0; i < vectorCountries.size(); i++)
	{
		cout << vectorCountries[i]->getName() << endl;
		vector<Country*> adjacentCountriesOf = world->AdjacentCountriesOwnedByPlayer(player, vectorCountries[i]);

		for (int j = 0; j < adjacentCountriesOf.size(); j++)
			cout << adjacentCountriesOf[j]->getName() << " (" << adjacentCountriesOf[j]->getArmySize() << "), ";

		cout << "\n" << endl;
	}

	validInput = false;

	while (!validInput)
	{
		cin.clear();
		cout << "\nFrom which country you want to move your armies? ";
		getline(cin, fromCountry);

		for (Country* c : player->getListCountriesOwned())
		{
			if (c->getName() == fromCountry && c->getArmySize() > 1)
			{
				validInput = true;
				break;
			}
		}
		if (!validInput)
		{
			cout << "\nThe Country entered is not Valid or the selected Country has only one army. " << endl;
		}
	}
	for (int i = 0; i < vectorCountries.size(); i++)
		if (vectorCountries[i]->getName() == fromCountry)
		{
			c = vectorCountries[i];
		}

	if (c == NULL)
	{
		throw exception("Error finding Country");
	}

	cout << "\nThere are " << c->getArmySize() << " armies in " << c->getName();

	cout << "\nHow many armies you want to move from that country? ";
	cin >> numberOfArmies;
	cout << (numberOfArmies < 1 && numberOfArmies > c->getArmySize());
	while (!cin || (numberOfArmies < 1 && numberOfArmies > c->getArmySize())) {
		cout << "\nHow many armies you want to move from that country? ";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> numberOfArmies;
	}
	c->removeArmies(numberOfArmies);


	bool validDestination = false;
	while (!validDestination)
	{
		cout << "Where is the destination countries? ";
		getline(cin, destinationCountry);
		for (Country* c : player->getListCountriesOwned())
		{

			if (c->getName() == destinationCountry)
			{
				validDestination = true;
				break;
				//todo check adjacency between the contries or is there is a path it can take to get there
			}
		}

	}

	Country* country1 = world->searchForCountry(fromCountry);
	Country* country2 = world->searchForCountry(destinationCountry);
	cout << "Debug++++++++++++++++++++++++++++++++++++++" << country1->getName() << endl;
	cout << "Debug++++++++++++++++++++++++++++++++++++++" << country2->getName() << endl;
	bool isPath = world->pathFindCountry(country1, country2, player);
	cout << "is Path __________________________________________------------" << isPath << endl;
	validDestination = isPath;
	for (int i = 0; i < vectorCountries.size(); i++)
		if (vectorCountries[i]->getName() == destinationCountry)
			vectorCountries[i]->addArmies(numberOfArmies);
}

void MainPhase::continentsChecking(Player* player)
{
	vector<Country*> listCountriesOwned = player->getListCountriesOwned();
	vector<Continent*> listContinentsOwned = player->getListContinentOwned();
	int africaCount = 0;
	int asiaCount = 0;
	int australiaCount = 0;
	int europeCount = 0;
	int northAmericaCount = 0;
	int southAmericaCount = 0;

	for (int i = 0; i < listCountriesOwned.size(); i++)
	{
		if ((listCountriesOwned[i]->getName() == "Congo") ||
			(listCountriesOwned[i]->getName() == "East Africa") ||
			(listCountriesOwned[i]->getName() == "Egypt") ||
			(listCountriesOwned[i]->getName() == "Madagascar") ||
			(listCountriesOwned[i]->getName() == "North Africa") ||
			(listCountriesOwned[i]->getName() == "South Africa"))
			africaCount++;

		if ((listCountriesOwned[i]->getName() == "Afghanistan") ||
			(listCountriesOwned[i]->getName() == "China") ||
			(listCountriesOwned[i]->getName() == "India") ||
			(listCountriesOwned[i]->getName() == "Irkustsk") ||
			(listCountriesOwned[i]->getName() == "Japan") ||
			(listCountriesOwned[i]->getName() == "Kamchatka") ||
			(listCountriesOwned[i]->getName() == "Middle East") ||
			(listCountriesOwned[i]->getName() == "Mongolia") ||
			(listCountriesOwned[i]->getName() == "Siam") ||
			(listCountriesOwned[i]->getName() == "Siberia") ||
			(listCountriesOwned[i]->getName() == "Ural") ||
			(listCountriesOwned[i]->getName() == "Yatusk"))
			asiaCount++;

		if ((listCountriesOwned[i]->getName() == "Eastern Australia") ||
			(listCountriesOwned[i]->getName() == "Indonesia") ||
			(listCountriesOwned[i]->getName() == "New Guinea") ||
			(listCountriesOwned[i]->getName() == "Western Australia"))
			australiaCount++;

		if ((listCountriesOwned[i]->getName() == "Great Britain") ||
			(listCountriesOwned[i]->getName() == "Iceland") ||
			(listCountriesOwned[i]->getName() == "Northern Europe") ||
			(listCountriesOwned[i]->getName() == "Scandinavia") ||
			(listCountriesOwned[i]->getName() == "Southern Europe") ||
			(listCountriesOwned[i]->getName() == "Ukraine") ||
			(listCountriesOwned[i]->getName() == "Western Europe"))
			europeCount++;

		if ((listCountriesOwned[i]->getName() == "Alaska") ||
			(listCountriesOwned[i]->getName() == "Alberta") ||
			(listCountriesOwned[i]->getName() == "Central America") ||
			(listCountriesOwned[i]->getName() == "Eastern United States") ||
			(listCountriesOwned[i]->getName() == "Greenland") ||
			(listCountriesOwned[i]->getName() == "Northwest Country") ||
			(listCountriesOwned[i]->getName() == "Ontario") ||
			(listCountriesOwned[i]->getName() == "Quebec") ||
			(listCountriesOwned[i]->getName() == "Western United States"))
			northAmericaCount++;

		if ((listCountriesOwned[i]->getName() == "Argentina") ||
			(listCountriesOwned[i]->getName() == "Brazil") ||
			(listCountriesOwned[i]->getName() == "Peru") ||
			(listCountriesOwned[i]->getName() == "Venezuala"))
			southAmericaCount++;
	}

	bool inTheList = false;
	if (africaCount == 6)
	{
		for (int i = 0; i < listContinentsOwned.size(); i++)
		{
			if (listContinentsOwned[i]->getName() == "Africa")
				inTheList = true;
			break;
		}

		if (!inTheList)
			player->addContinentToList("Africa", 3);

		inTheList = false;

	}
	else
	{
		for (int i = 0; i < listContinentsOwned.size(); i++)
		{
			if (listContinentsOwned[i]->getName() == "Africa")
				inTheList = true;
			break;
		}

		if (inTheList)
		{
			player->removeContinentFromList("Africa");
			inTheList = false;
		}
			
	}


	if (asiaCount == 12)
	{
		for (int i = 0; i < listContinentsOwned.size(); i++)
		{
			if (listContinentsOwned[i]->getName() == "Asia")
				inTheList = true;
			break;
		}

		if (!inTheList)
			player->addContinentToList("Asia", 7);

		inTheList = false;

	}
	else
	{
		for (int i = 0; i < listContinentsOwned.size(); i++)
		{
			if (listContinentsOwned[i]->getName() == "Asia")
				inTheList = true;
			break;
		}

		if (inTheList)
		{
			player->removeContinentFromList("Asia");
			inTheList = false;
		}

	}

	if (australiaCount == 4)
	{
		for (int i = 0; i < listContinentsOwned.size(); i++)
		{
			if (listContinentsOwned[i]->getName() == "Australia")
				inTheList = true;
			break;
		}

		if (!inTheList)
			player->addContinentToList("Australia", 2);

		inTheList = false;

	}
	else
	{
		for (int i = 0; i < listContinentsOwned.size(); i++)
		{
			if (listContinentsOwned[i]->getName() == "Australia")
				inTheList = true;
			break;
		}

		if (inTheList)
		{
			player->removeContinentFromList("Australia");
			inTheList = false;
		}

	}

	if (europeCount == 7)
	{
		for (int i = 0; i < listContinentsOwned.size(); i++)
		{
			if (listContinentsOwned[i]->getName() == "Europe")
				inTheList = true;
			break;
		}

		if (!inTheList)
			player->addContinentToList("Europe", 5);

		inTheList = false;

	}
	else
	{
		for (int i = 0; i < listContinentsOwned.size(); i++)
		{
			if (listContinentsOwned[i]->getName() == "Europe")
				inTheList = true;
			break;
		}

		if (inTheList)
		{
			player->removeContinentFromList("Europe");
			inTheList = false;
		}

	}

	if (northAmericaCount == 9)
	{
		for (int i = 0; i < listContinentsOwned.size(); i++)
		{
			if (listContinentsOwned[i]->getName() == "North America")
				inTheList = true;
			break;
		}

		if (!inTheList)
			player->addContinentToList("North America", 5);

		inTheList = false;

	}
	else
	{
		for (int i = 0; i < listContinentsOwned.size(); i++)
		{
			if (listContinentsOwned[i]->getName() == "North America")
				inTheList = true;
			break;
		}

		if (inTheList)
		{
			player->removeContinentFromList("North America");
			inTheList = false;
		}

	}

	if (southAmericaCount == 4)
	{
		for (int i = 0; i < listContinentsOwned.size(); i++)
		{
			if (listContinentsOwned[i]->getName() == "South America")
				inTheList = true;
			break;
		}

		if (!inTheList)
			player->addContinentToList("South America", 2);

		inTheList = false;

	}
	else
	{
		for (int i = 0; i < listContinentsOwned.size(); i++)
		{
			if (listContinentsOwned[i]->getName() == "South America")
				inTheList = true;
			break;
		}

		if (inTheList)
		{
			player->removeContinentFromList("South America");
			inTheList = false;
		}

	}
}
