#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Country
{
public:
	//this is a mess
	Country();
	Country(string Name);
	Country(string name, int xpos, int ypos);
	Country(string name, int num, string owner);
	~Country();

	string getName();
	void setName(string value);

	string getContinent();
	void setContinent(string value);

	int getArmySize();
	void addArmies(int numberToAdd);
	void removeArmies(int numberToRemove);

	void setBoarders(vector<Country*> continent);
	void addBoarders(Country* country);
	vector<Country*> getBoarders();

	string getOwner();
	void setOwner(string value);

	int getX();
	int getY();
	void addAdjacentTerritory(Country*);
	bool isAdjacentTerritory(Country*);
	vector<Country*> getAdjacentCountriesOfOtherPlayers(Country* country, string player);
	vector<Country*> getAdjacentTerritories();
	void removeAdjacentTerritory(Country*);
	void print();
	void printAdjacency();
	bool marked;

private:
	string name;
	string continent;
	int armySize;
	string ownerName;
	int _posX;
	int _posY;
	vector <Country*> _adjacentTerritories;
	string onwer;
};

