#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <ctime>

#include "StartupPhase.h"
#include "Player.h"
#include "MapDriver.h"

using namespace std;

StartupPhase::StartupPhase() // Constructor
{
	MapDriver mdriver;

	cout << "Welcome to MapManager" << endl;
	string answer;
	bool validAnswer = false;

	// load or start from scratch
	while (!validAnswer)
	{
		cout << "Do you want to load an existing file (l) or start from scratch (s)?" << endl;
		getline(cin, answer);
		if (answer.compare("l") == 0) {
			// load existing file
			validAnswer = mdriver.load();
		}
		else if (answer.compare("s") == 0) {
			// start from scratch
			// create world
			validAnswer = mdriver.scratch();
		}
		else {
			cout << "I didn't understand" << endl;
		}
	}

	mdriver.mainMenu();
	currentWorld = mdriver.getCurrentWorld();
}

World* StartupPhase::getCurrentWorld()
{
	return currentWorld;
}

vector<Player*> StartupPhase::asksPlayersNames() // Asks the players name
{
	int totalNumberPlayer;
	bool validInput = false;

	int input;
	// Asks how many players are going to play
	cout << "Enter the number of players (2 - 5 players): ";
	cin >> totalNumberPlayer;
	while (!cin || totalNumberPlayer < 2 || totalNumberPlayer > 5) {
		cout << "\nEnter the number of players (2 - 5 players):";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> totalNumberPlayer;
	}


	vector<Player*> vectorPlayers;
	string name;

	// Pushes in the vectors the Player objects
	for (int i = 1; i <= totalNumberPlayer; i++)
	{
		cout << "Player " << i << " - Enter your name: ";
		cin >> name;

		vectorPlayers.push_back(new Player(name, i));
	}

	return vectorPlayers;
}

void StartupPhase::assignCountryRandomly(vector<Player*> vectorPlayers, map<string, Country*> countries) // Assigns randomly countries to the players
{
	int countriesPerPlayer = floor(countries.size() / vectorPlayers.size());
	int numberOfUnclaimedCountries = countries.size() % vectorPlayers.size();

	// Randomly assigns countries equally
	for (map<string, Country*>::iterator it = countries.begin(); it != countries.end(); ++it)
	{
		bool timeToAssignUnclaimedCountries = false;
		bool isAssigned = false;
		while (!isAssigned)
		{
			int playerNumber = rand() % vectorPlayers.size();

			if (vectorPlayers[playerNumber]->getListCountriesOwned().size() < countriesPerPlayer)
			{
				it->second->setOwner(vectorPlayers[playerNumber]->getPlayerName());
				it->second->addArmies(1);
				vectorPlayers[playerNumber]->removeReinforcementNumber(1);
				vectorPlayers[playerNumber]->addCountryToList(it->second);
				isAssigned = true;
			}
			else
			{
				for (int i = 0; i < vectorPlayers.size(); i++)
					if (vectorPlayers[i]->getListCountriesOwned().size() != countriesPerPlayer)
						break;
					else
					{
						timeToAssignUnclaimedCountries = true;
					}
			}

			if (timeToAssignUnclaimedCountries)
			{
				it->second->setOwner(vectorPlayers[playerNumber]->getPlayerName());
				it->second->addArmies(1);
				vectorPlayers[playerNumber]->removeReinforcementNumber(1);
				vectorPlayers[playerNumber]->addCountryToList(it->second);
				isAssigned = true;
			}

		}
	}
}

void StartupPhase::giveOutInitialArmies(vector<Player*> vectorPlayers) // Gives out the initial armies to the players
{
	int numberOfPlayers = vectorPlayers.size();
	int numberOfArmies = 0;

	switch (numberOfPlayers)
	{
	case 2:
		numberOfArmies = 40;
		break;
	case 3:
		numberOfArmies = 35;
		break;
	case 4:
		numberOfArmies = 30;
		break;
	case 5:
		numberOfArmies = 25;
		break;
	}

	for (int i = 0; i < numberOfPlayers; i++)
		vectorPlayers[i]->addReinforcementNumber(numberOfArmies);
}

void StartupPhase::loadMap(string fileMapName) // Loads the chosen map
{
	currentMap = new MapIni(fileMapName);    // Call main_menu() in mapDriver class?
}
