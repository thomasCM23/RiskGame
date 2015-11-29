#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

#include "Player.h"
#include "PlayerView.h"
#include "MapIni.h"
#include "StartupPhase.h"
#include "MainPhase.h"

using namespace std;

int main()
{
	vector<Player*> vectorPlayers; // Vector containing Player objects
	
	// Displays a welcome message
	cout << "===============================================" << endl;
	cout << setw(42) << "--== Welcome to the game of Risk ==--" << endl;
	cout << "===============================================\n" << endl;

	// Startup Phase
	cout << setw(35) << "----- Startup Phase -----\n" << endl;

	StartupPhase startupPhase;
	World *worldObj = startupPhase.getCurrentWorld();

	vectorPlayers = startupPhase.asksPlayersNames(); // Asks the players names and creates a Player Object for each of them
	
	map<string, Country*> allcountries = worldObj->getTerritories();

	//Add Observers
	for (Player* p : vectorPlayers)
	{
		PlayerView *playerView = new PlayerView(p);
	}

	startupPhase.giveOutInitialArmies(vectorPlayers); // Gives out an initial number of armies to the players
	startupPhase.assignCountryRandomly(vectorPlayers, allcountries); // Assigns randomly the initial countries to the players 

	cout << "===============================================\n" << endl;

	// Main Phase
	cout << setw(34) << "----- Main Phase ------\n" << endl;

	// Randomly choose who starts the game first
	srand(time(0));
	int starter = 1 + rand() % vectorPlayers.size();
	int playerNumber = starter - 1;

	cout << "Randomly chosen - Player " << starter << ": " << vectorPlayers[playerNumber]->getPlayerName() << ", you play first !\n" << endl;
	cout << "===============================================\n" << endl;

	MainPhase mainPhase;

	// Implementation of the ordering of the phases (Round-robin loop over the players)
	while (vectorPlayers.size() > 1)
	{
		PlayerView *playerView = new PlayerView(vectorPlayers[playerNumber]);
		cout << "PLAYER " << playerNumber + 1 << " TURN.\n" << endl;

		// Reinforcement phase for the current player
		cout << "--> Reinforcement Phase\n" << endl;
		mainPhase.reinforce(vectorPlayers[playerNumber]);

		// Attack phase for the current player
		cout << "\n--> Attack Phase\n" << endl;
		mainPhase.attack(vectorPlayers[playerNumber], allcountries, vectorPlayers);

		// Fortification phase for the current player
		cout << "--> Fortification Phase\n" << endl;
		mainPhase.fortification(vectorPlayers[playerNumber], worldObj);

		cout << "\nPLAYER " << playerNumber + 1 << " TURN HAS ENDED.\n" << endl;
		cout << "====================================================================\n" << endl;

		// Increments the playerNumber in order to give control to the next player
		playerNumber++;
		if (playerNumber >= vectorPlayers.size()) // If it reaches the total number of players, resets it back to 0 (loop it around, round-robin)
			playerNumber = 0;

		delete playerView;
	}
	


	Player* winner = NULL;
	for (Player* p : vectorPlayers)
	{
		if (p != NULL)
			winner = p;
	}
	if (winner != NULL)
		cout << "Game Over! The winner is: " << winner->getPlayerName();

	system("pause");
	return 0;
}