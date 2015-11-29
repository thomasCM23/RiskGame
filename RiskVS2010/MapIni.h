#ifndef MAP_INI_H
#define MAP_INI_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <list>
#include "Continent.h"
#include "Country.h"
#include "Country.h"
#include "World.h"
#include "Player.h"
#include "IniParser.h"

using namespace std;

class MapIni
{
public:

	MapIni(map<string, Continent*> continents, map<string, Country*> countries);
	MapIni(string fileName);
	map<string, string> getMapInfo();
	map<string, Continent*> getContinents();
	map<string, Country*> getTerritories();
	map<string, list<string>> getAdjacency();
	Country* getCountry(string name);
	bool writeMapToFile(map<string, string>, string);
	bool writeWorldToFile(World, string);
	vector<Country*> getAdjacentCountriesOfOtherPlayers(Country* country, Player& player);
	~MapIni(void);

private:
	string _fileName;
	map<string, string> _mapInfo;
	map<string, Continent*> _continents;
	map<string, Country*> _territories;
	map<string, list<string>> _adjacentTerritories;
	IniParser* _parser;
	void readMapInfo();
	void readContinents();
	void readTerritories();
};

#endif