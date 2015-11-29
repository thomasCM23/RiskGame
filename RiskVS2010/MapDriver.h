#ifndef MAPDRIVER_H
#define MAPDRIVER_H

#include "MapIni.h"
#include "Country.h"
#include "Continent.h"
#include "World.h"
#include "stdafx.h"

class MapDriver
{
public:
	MapDriver();
	void showWorldDetails(World*);
	void mainMenu();
	void askNewCountry();
	void askDefineCountryRelationship();
	void askNewContinent();
	void askManageContinent();
	World* getCurrentWorld();
	bool scratch();
	bool load();
	bool save();
private:
	MapIni* loadedMap = NULL;
	World* earth = NULL;
};

#endif
