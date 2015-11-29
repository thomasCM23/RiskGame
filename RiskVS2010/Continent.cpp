#include "stdafx.h"
#include <algorithm>
#include "Continent.h"

Continent::Continent(string name, int bonus):
	_name(name),
	_bonusOwning(bonus)
{
}

string Continent::getName()
{
	return _name;
}

int Continent::getBonus()
{
	return _bonusOwning;
}

vector<Country*> Continent::getTerritories()
{
	return _territories;
}

Country * Continent::getTerritory(string country)
{
	for (int i = 0; i < _territories.size(); i++)
		if (_territories[i]->getName() == country)
			return _territories[i];
}

void Continent::addTerritory(Country* newTerritory)
{
	_territories.push_back(newTerritory);
}

void Continent::removeTerritory(Country* territory)
{
	for (vector<Country*>::size_type i=0; i<_territories.size(); i++)
	{
		if (_territories[i]->getName() == territory->getName()) {
			_territories.erase(_territories.begin() + i);
			break;
		}
	}
}

Country* Continent::removeTerritory(string territoryName)
{
	Country* terr = NULL;

	// remove territory from list
	for (vector<Country*>::size_type i=0; i<_territories.size(); i++)
	{
		if (_territories[i]->getName() == territoryName) {
			vector<Country*> adjCountries = _territories[i]->getAdjacentTerritories();

			// remove territory from adjacent territories
			// assume adjacent countries are reciprocal
			for (vector<Country*>::size_type j=0; j<adjCountries.size(); j++)
			{
				adjCountries[j]->removeAdjacentTerritory(_territories[i]);
			}

			terr = _territories[i];
			_territories.erase(_territories.begin() + i);
			i--;
		}
	}

	return terr;
}

void Continent::print()
{
	cout << "Continent " << getName();
	cout << " has " << getBonus() << " points of bonus for owning one of its territories,";
	if (_territories.size() == 0)
	{
		cout << " does not contain any territory";
	}
	else
	{
		cout << " contains the " << _territories.size() << " following territories: ";
		for (vector<Country*>::size_type i=0; i<_territories.size(); i++)
		{
			cout << _territories.at(i)->getName();
			if (i+1 != _territories.size())
				cout << ", ";
		}
	}
	cout << "." << endl;
}
Continent::Continent(string name)
{

	//read file of countries
	this->_name = name;
	std::ifstream fin;
	fin.open(name + ".txt");
	std::string nameOfCountry;
	if (fin.is_open())
	{
		while (getline(fin, nameOfCountry))
		{
			Country *toBePushed;	
			toBePushed = new Country(nameOfCountry, 0, name);
			this->_territories.push_back(toBePushed);
		}
	}
	fin.close();
}
Continent::~Continent(){}

void Continent::setContinent(std::vector<Country*> listOfContries)
{
	_territories = listOfContries;
}
bool Continent::isInContinent(Country * country)
{
	for (int i = 0; i < _territories.size(); i++)
		if (_territories[i]->getName() == country->getName())
			return true;

	return false;
}
std::vector<Country*> Continent::getContinent()
{
	return this->_territories;
}
void Continent::addCountryToContinent(Country* newCountry)
{
	this->_territories.push_back(newCountry);
}
Country* Continent::getInfoAboutCountryByIndex(int index)
{
	return _territories.at(index);
}