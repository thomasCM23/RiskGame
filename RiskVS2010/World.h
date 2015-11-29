#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <string>
#include <map>
#include <list>
#include "Continent.h"
#include "Player.h"
#include "Country.h"
#include <queue>
using namespace std;

class World
{
public:
	World(string ks);
	World();
	~World();
	string getName();
	map<string, string> getInfo();
	void setInfo(map<string, string>);
	void addTerritory(Country* country);
	void removeTerritory(Country* country);
	Country* removeTerritory(string territory);
	void addAdjacency(map<string, list<string>>);
	map<string, Continent*> getContinents();
	map<string, Country*> getTerritories();
	Continent* getContinent(string continent);
	Country* getTerritory(string territorry);
	void addContinent(Continent* continent);
	Continent* removeContinent(string continent);
	void destroyContinent(string continent);
	bool check();
	void print();

	void addContinent(Continent T);
	void loadContinentsFromFile();
	vector<Continent> getWorld();
	vector<Country> getContinentbyIndex(int index);
	Country* searchForCountry(string name);
	bool isCountryAdjacent(Country* country1, Country* country2);
	bool pathFindCountry(Country* country1, Country* country2, Player * player);
	vector<Country*> getAllAdjacentContries(Country* country);
	vector<Country*> AdjacentCountriesOwnedByPlayer(Player* player, Country * country);

private:
	string _name;
	map<string, Country*> _territories;
	map<string, Continent*> _continents;
	map<string, string> _mapInfo;
	vector<Continent> world;
protected:
	void instantiateMapLinks();
};

#endif