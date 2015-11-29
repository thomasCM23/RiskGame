#include "stdafx.h"
#include "Country.h"

Country::Country() {}

Country::Country(string Name)
{
	armySize = 0;
	setName(name);
}


Country::~Country()
{
}

string Country::getName()
{
	return name;
}

void Country::setName(string value)
{
	name = value;
}

string Country::getContinent()
{
	return continent;
}

void Country::setContinent(string value)
{
	continent = value;
}

int Country::getArmySize()
{
	return armySize;
}

void Country::addArmies(int numberToAdd)
{
	armySize += numberToAdd;
}

void Country::removeArmies(int numberToRemove)
{
	if (armySize > 0)
		armySize -= numberToRemove;
}

string Country::getOwner()
{
	return ownerName;
}

void Country::setOwner(string value)
{
	ownerName = value;
}
Country::Country(string name, int posX, int posY)
{
	armySize = 0;
	this->name = name;
	this->_posX = posX;
	this->_posY = posY;
}

int Country::getX()
{
	return _posX;
}

int Country::getY()
{
	return _posY;
}

void Country::addAdjacentTerritory(Country* newTerritory)
{
	if (!this->isAdjacentTerritory(newTerritory))
		_adjacentTerritories.push_back(newTerritory);
}

bool Country::isAdjacentTerritory(Country* newTerritory)
{
	for (vector<Country*>::size_type i = 0; i<_adjacentTerritories.size(); i++)
	{
		if (_adjacentTerritories[i]->getName() == newTerritory->getName())
			return true;
	}
	return false;
}

vector<Country*> Country::getAdjacentTerritories()
{
	return _adjacentTerritories;
}

void Country::removeAdjacentTerritory(Country* territory)
{
	for (vector<Country*>::size_type i = 0; i<_adjacentTerritories.size(); i++)
	{
		if (_adjacentTerritories[i]->getName() == territory->getName()) {
			_adjacentTerritories.erase(_adjacentTerritories.begin() + i);
			break;
		}
	}
}

void Country::print()
{
	cout << "Territory " << getName();
	cout << " centered at (" << getX() << "," << getY() << "),";
	if (_adjacentTerritories.size() == 0)
	{
		cout << " does not have any adjacent territories";
	}
	else
	{
		cout << " is adjacent to the " << _adjacentTerritories.size() << " following territories: ";
		for (vector<Country*>::size_type i = 0; i<_adjacentTerritories.size(); i++)
		{
			cout << _adjacentTerritories.at(i)->getName();
			if (i + 1 != _adjacentTerritories.size())
				cout << ", ";
		}
	}
	cout << "." << endl;
}
void Country::printAdjacency()
{
	cout << "Adjacent countries: ";
	for (int i = 0; i < _adjacentTerritories.size(); i++)
		cout << _adjacentTerritories[i]->getName() << ", ";
	cout << "\n" << endl;
}
vector<Country*> Country::getAdjacentCountriesOfOtherPlayers(Country* country, string player)
{
	vector<Country*> voidctries;
	return voidctries;
}

Country::Country(std::string name, int num, string owner)
{
	this->name = name;
	this->armySize = num;
	this->onwer = owner;
}
void Country::addBoarders(Country* T)
{
	this->_adjacentTerritories.push_back(T);
}
void Country::setBoarders(std::vector<Country*> T)
{
	this->_adjacentTerritories = T;
}
std::vector<Country*> Country::getBoarders()
{
	return this->_adjacentTerritories;
}
