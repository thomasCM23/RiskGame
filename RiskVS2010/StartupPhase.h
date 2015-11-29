#ifndef STARTUPPHASE_H
#define STARTUPPHASE_H

#include "Player.h"
#include "MapIni.h"

// Startup phase object
class StartupPhase
{
public:
	StartupPhase(); // Constructor
	vector<Player*> asksPlayersNames(); // Function that asks for the players name
	void assignCountryRandomly(vector<Player*> vectorPlayers, map<string, Country*> countries); // Function that assigns randomly countries to players
	void giveOutInitialArmies(vector<Player*> vectorPlayers); // Function that give out the initial armies to every players
	void loadMap(string fileMapName); // Function that loads the chosen map
	World* getCurrentWorld();

private:
	MapIni* currentMap;
	World* currentWorld;
};
#endif
