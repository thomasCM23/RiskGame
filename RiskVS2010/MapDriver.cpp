#include "stdafx.h"
#include <iostream>
#include "MapIni.h"
#include "Country.h"
#include "Continent.h"
#include "World.h"
#include "MapDriver.h"


//Namespaces
using namespace std;

MapDriver::MapDriver()
{

}

void MapDriver::mainMenu()
{
	// what to do
	cout << endl;
	cout << "What do you want to do? Choose from the following list: " << endl << endl;
	string answer;

	cout << "0. Show current configuration" << endl;
	cout << "1. Create a country" << endl;
	cout << "2. Define the adjacency relationships between countries" << endl;
	cout << "3. Create continent" << endl;
	cout << "4. Assign countries to a continent" << endl;
	cout << "5. Save to file" << endl;
	cout << "6. Exit (no saving)" << endl;
	cout << endl;
	cout << "> ";

	getline(cin, answer);
	if (answer.compare("0") == 0) {
		// show everything
		showWorldDetails(earth);
		mainMenu();
	}
	else if (answer.compare("1") == 0) {
		// new country
		askNewCountry();
		mainMenu();
	}
	else if (answer.compare("2") == 0) {
		// country relationship
		askDefineCountryRelationship();
		mainMenu();
	}
	else if (answer.compare("3") == 0) {
		// country relationship
		askNewContinent();
		mainMenu();
	}
	else if (answer.compare("4") == 0) {
		// country relationship
		askManageContinent();
		mainMenu();
	}
	else if (answer.compare("5") == 0) {
		// save
		save();
		mainMenu();
	}
	else if (answer.compare("6") == 0) {
		// exit
		cout << "Exiting" << endl;
		// nothing
	}
	else {
		cout << "I didn't understand" << endl;
		mainMenu(); //reask
	}
}

World* MapDriver::getCurrentWorld(){
	return earth;
}

void MapDriver::showWorldDetails(World* myWorld)
{
	// print included continents
	myWorld->print();
	cout << endl;

	// display continents info
	map<string, Continent*> continents = myWorld->getContinents();
	for (map<string, Continent*>::iterator it = continents.begin(); it != continents.end(); ++it)
	{
		it->second->print();

		// print territories details
		vector<Country*> territories = it->second->getTerritories();
		for (vector<Country*>::size_type i = 0; i<territories.size(); i++)
		{
			territories[i]->print();
		}
		cout << endl;
	}
}

void MapDriver::askNewCountry()
{
	string countryName;
	int countryPosX;
	int countryPosY;
	string tmp;
	vector<string> emptyAdj;
	bool valid = false;
	cout << "Enter the name of the new country: ";
	getline(cin, countryName);


	while(!valid)
	{
		cout << "Enter the X position: ";
		getline(cin, tmp);
		countryPosX = atoi(tmp.c_str());

		cout << "Enter the Y position: ";
		getline(cin, tmp);
		countryPosY = atoi(tmp.c_str());
	
		map<string, Country*> cont = earth->getTerritories();

		valid = true;
		for (map<string, Country*>::iterator it = cont.begin(); it != cont.end(); ++it){
			if (countryPosX == it->second->getX() && countryPosY == it->second->getY())
			{
				cout << "There is already a Country at this location. Please select a different Location" << endl;
				valid = false;
				break;
			}	
		}
	}

	if (valid){
		earth->addTerritory(
			new Country(countryName, countryPosX, countryPosY));
		cout << "Country added!" << endl;
	}

}

void MapDriver::askDefineCountryRelationship()
{
	string answer;
	string c1, c2;
	Country *country1, *country2;
	cout << "Existing countries:" << endl << endl;

	map<string, Country*> cont = earth->getTerritories();
	for (map<string, Country*>::iterator it = cont.begin(); it != cont.end(); ++it)
	{
		cout << it->second->getName() << " <" << it->second->getX() << "," << it->second->getY() << "> ";

		// list current adj
		cout << "(";
		it->second->printAdjacency();
		cout << ")" << endl;
	}

	if (cont.size()<2) {
		cout << "Need to define at least one more country!" << endl;
		return;
	}

	cout << endl;
	cout << "Enter first country to pair: ";
	getline(cin, c1);;
	cout << "Enter second country to pair: ";
	getline(cin, c2);

	// get c1 and c2
	country1 = earth->getTerritory(c1);
	country2 = earth->getTerritory(c2);

	if (country1 != NULL && country2 != NULL) {
		// assign each other as adjacent country
		country1->addAdjacentTerritory(country2);
		country2->addAdjacentTerritory(country1);

		cout << "Paired!" << endl;
	}
	else {
		cout << "Couldn't find one of the countries" << endl;
	}
}

void MapDriver::askNewContinent()
{
	string continentName, tmp;
	int score;

	cout << "Enter the name of the new continent: ";
	getline(cin, continentName);

	cout << "Enter score for owning the continent: ";
	getline(cin, tmp);
	score = atoi(tmp.c_str());

	earth->addContinent(new Continent(continentName, score));

	cout << "Continent created!" << endl;
}

void MapDriver::askManageContinent()
{
	string answer;
	string continentName;
	string countryName;

	cout << "Existing continents:" << endl;
	map<string, Continent*> cont = earth->getContinents();
	for (map<string, Continent*>::iterator it = cont.begin(); it != cont.end(); ++it)
	{
		cout << it->second->getName() << endl;
	}
	cout << endl;

	cout << "Unassigned countries:" << endl;
	map<string, Country*> countries = earth->getTerritories();
	
	for (map<string, Country*>::iterator it = countries.begin(); it != countries.end(); ++it)
	{
		bool isAssigned = false;
		for (map<string, Continent*>::iterator it2 = cont.begin(); it2 != cont.end(); ++it2)
		{
			if (it2->second->isInContinent(it->second)) {
				isAssigned = true;
				break;
			}
		}

		if (!isAssigned) {
			cout << it->second->getName() << " ";
			cout << "(";
			it->second->printAdjacency();
			cout << ")" << endl;
		}
	}

	cout << endl;
	cout << "Enter the continent you want to assign a country to: ";
	getline(cin, continentName);

	Continent* continent = NULL;
	if ((continent = earth->getContinent(continentName)) == NULL) {
		cout << "Continent doesn't exist" << endl;
		return;
	}

	cout << "Enter the country you want to assign to " << continent->getName() << ": ";
	getline(cin, countryName);

	Country* country = NULL;
	if ((country = earth->getTerritory(countryName)) == NULL) {
		cout << "Country doesn't exist" << endl;
		return;
	}

	continent->addTerritory(country);

	cout << "The country " << country->getName() << " was added to the continent "
		<< continent->getName() << "!" << endl;
}

bool MapDriver::scratch()
{
	earth = new World("Earth");
	map<string, string> mapInfo;
	mapInfo["author"] = "MapManager";
	earth->setInfo(mapInfo);
	return true;
}

bool MapDriver::load()
{
	string fileName;
	cout << "Enter the location of the file to load: ";
	getline(cin, fileName);
	try
	{
		// load map
		loadedMap = new MapIni(fileName);
		// create world
		earth = new World("Earth");

		// retrieve info
		earth->setInfo(loadedMap->getMapInfo());
		map<string, Country*> countries = loadedMap->getTerritories();
		map<string, list<string>> adjacency = loadedMap->getAdjacency();
		map<string, Continent*> continents = loadedMap->getContinents();

		// list territories and fill the world
		for (map<string, Country*>::iterator it = countries.begin(); it != countries.end(); ++it)
		{
			// add territory to world
			earth->addTerritory(it->second);
		}

		// assign adjacancy
		earth->addAdjacency(adjacency);

		// list continents and fill the world
		for (map<string, Continent*>::iterator it = continents.begin(); it != continents.end(); ++it)
		{
			// add continent to world
			earth->addContinent(it->second);
		}
		delete loadedMap;
	}
	catch (...)
	{
		if (loadedMap != NULL)
		{
			delete loadedMap;
			loadedMap = NULL;
		}
		if (earth != NULL)
		{
			delete earth;
			earth = NULL;
		}
		return false;
	}
	cout << "Loaded successfully!" << endl;
	return true;
}

bool MapDriver::save()
{



	string fileName;
	cout << "Enter the location of the file to save: ";
	getline(cin, fileName);

	try
	{
		MapIni map(earth->getContinents(), earth->getTerritories());
		if (map.writeWorldToFile(*earth, fileName))
		{
			cout << "Map Saved sucessfully!" << endl;
		}
		else
			cout << "Map do not Save! Please try again!" << endl;
	}
	catch (...)
	{
		return false;
	}
	
	return true;
}
