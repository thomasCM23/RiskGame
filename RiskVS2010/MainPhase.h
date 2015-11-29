#ifndef MAINPHASE_H
#define MAINPHASE_H

#include "Player.h"
#include "Country.h"
#include "Battle.h"
#include "World.h"

// Main phase object
class MainPhase
{
public:
	MainPhase(); // Constructor
	void reinforce(Player* player); // Reinformence phase
	void attack(Player* player, map<string, Country*> allCountries, vector<Player*> players); // Attack phase
	void fortification(Player* player, World* world); // Fortificition phase

private:
	void continentsChecking(Player* player);
	void cardsOneOfEach(Player* player);
	void cardsThreeSame(Player* player);
	void putArmiesInCountries(Player* player); // Puts the number of armies inside the given country
	void moveArmies(Player* player, World* world); // Moves the given number of armies to another owned country
};

#endif