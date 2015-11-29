#ifndef CONTINENT_H
#define CONTINENT_H
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <regex>
#include <sstream>
#include "Country.h"
using namespace std;

class Continent
{
public:
	Continent(string, int);
	~Continent();
	string getName();
	int getBonus();
	vector<Country*> getTerritories();
	Country* getTerritory(string);
	void addTerritory(Country*);
	void removeTerritory(Country*);
	Country* removeTerritory(string);
	void print();

	Continent(string name);
	Country* getInfoAboutCountryByIndex(int index);
	vector<Country*> getContinent();
	void addCountryToContinent(Country* newContry);
	void setContinent(std::vector<Country*> listOfCountries);
	bool isInContinent(Country* country);

private:
	string _name;
	int _bonusOwning;
	vector<Country*> _territories;
};

#endif