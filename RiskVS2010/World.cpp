#include "stdafx.h"
#include <algorithm>
#include "World.h"

World::World(string name) :
_name(name)
{
}

string World::getName()
{
	return _name;
}

map<string, string> World::getInfo()
{
	return _mapInfo;
}

void World::setInfo(map<string, string> mapInfo)
{
	_mapInfo = mapInfo;
}

void World::addTerritory(Country* newTerritory)
{
	_territories[newTerritory->getName()] = newTerritory;
}

void World::removeTerritory(Country* territory)
{
	vector<Country*> adjCountries = territory->getAdjacentTerritories();

	// remove territory from adjacent territories
	// assume adjacent countries all in one country
	for (vector<Country*>::size_type j = 0; j<adjCountries.size(); j++)
	{
		adjCountries[j]->removeAdjacentTerritory(territory);
	}

	// remove from the list
	_territories.erase(territory->getName());
}

Country* World::removeTerritory(string territoryName)
{
	Country* terr = NULL;

	if (_territories.find(territoryName) != _territories.end())
	{
		terr = _territories[territoryName];
		this->removeTerritory(terr);
	}
	return terr;
}

void World::addAdjacency(map<string, list<string>> adjacency)
{
	for (map<string, list<string>>::iterator it = adjacency.begin(); it != adjacency.end(); it++)
	{
		if (_territories.find(it->first) == _territories.end())
		{
			cout << "Cannot assign adjacency for unknown territory " << it->first << endl;
			throw;
		}
		list<string> adj = it->second;
		for (list<string>::iterator it2 = adj.begin(); it2 != adj.end(); it2++)
		{
			if (_territories.find(*it2) == _territories.end())
			{
				cout << "Cannot assign adjacency to unknown territory " << *it2 << endl;
				throw;
			}
			_territories[it->first]->addAdjacentTerritory(_territories[*it2]);
		}
	}
}

map<string, Continent*> World::getContinents()
{
	return _continents;
}

map<string, Country*> World::getTerritories()
{
	return _territories;
}

Continent* World::getContinent(string continentName)
{
	if (_continents.find(continentName) != _continents.end())
	{
		return _continents[continentName];
	}
	return NULL;
}

Country * World::getTerritory(string countryName)
{
	if (_territories.find(countryName) != _territories.end())
	{
		return _territories[countryName];
	}
	return NULL;
}

void World::addContinent(Continent* continent)
{
	_continents[continent->getName()] = continent;
}

Continent* World::removeContinent(string continentName)
{
	Continent* cont = NULL;
	if (_continents.find(continentName) != _continents.end())
	{
		cont = _continents[continentName];
		_continents.erase(continentName);
	}
	return cont;
}

void World::destroyContinent(string continent)
{
	//TODO METHOD MISSING
}

bool World::check()
{
	//enforce connected graph
	// graph nodes are found in _territories
	// continents are collection of Country*, should check if
	// continents are connected subgraphs, where each country belongs to one and
	// only one continent

	//territory cannot exist twice because map<string, Country*> allows unique key only for names

	return true;
}

void World::print()
{
	cout << "World " << getName();
	if (_continents.size() == 0)
	{
		cout << " does not contain any continent";
	}
	else
	{
		cout << " contains the " << _continents.size() << " following continent: ";
		for (map<string, Continent*>::iterator it = _continents.begin(); it != _continents.end();)
		{
			cout << it->first;
			if ((++it) != _continents.end())
				cout << ", ";
		}
	}
	cout << "." << endl;
}

void World::addContinent(Continent T)
{
	//TODO METHOD MISSING
}

void World::loadContinentsFromFile()
{
	//TODO METHOD MISSING
}

vector<Continent> World::getWorld()
{
	return world;
}

vector<Country> World::getContinentbyIndex(int index)
{
	//TODO IMPLEMENT
	return vector<Country>();
}




World::World()
{
	//read file of continents
	ifstream fin;
	fin.open("Continents.txt");
	if (fin.is_open()){
		string temp;
		while (getline(fin, temp))
		{
			Continent pushedInRiskGraph(temp);
			this->world.push_back(pushedInRiskGraph);
		}
	}
	fin.close();
	World::instantiateMapLinks();
	/*for (int i = 0; i < RiskMap::world.size(); i++)
	{
	RiskMap::world.at(i).InstantiateMapLinks();
	}*/
}


void World::instantiateMapLinks()
{
	std::cout << "Setting up map..." << endl;
	for (int i = 0; i < this->world.size(); i++)
	{
		std::cout << "-------------" << endl;
		std::cout << this->world.at(i).getName() << endl;
		std::cout << endl;
		Continent *Continent = &this->world.at(i);
		for (int j = 0; j < Continent->getContinent().size(); j++)
		{
			ifstream boarders;
			boarders.open("boarders.txt");
			std::cout << (Continent->getContinent().at(j)->getName()) << ":  ";

			regex nameOfCountryRx("^" + (Continent->getContinent().at(j)->getName()) + "(.*)");
			while (!boarders.eof())
			{
				string lineInBoarderTxt;
				getline(boarders, lineInBoarderTxt);
				if (regex_match(lineInBoarderTxt, nameOfCountryRx))
				{
					size_t pos = lineInBoarderTxt.find(":");
					int first = (int)pos + 1;
					lineInBoarderTxt = lineInBoarderTxt.substr(first, lineInBoarderTxt.length());
					istringstream ss(lineInBoarderTxt);
					string split;
					while (std::getline(ss, split, ','))
					{
						for (int k = 0; k < Continent->getContinent().size(); k++)
						{
							if (Continent->getContinent().at(k)->getName() == split)
							{
								Continent->getContinent().at(j)->addBoarders(Continent->getContinent().at(k));
								std::cout << split << ", ";
								break;
							}
							else
							{
								//looking through other continents to find the node
								Country* prt = this->searchForCountry(split);
								if (prt != nullptr)
								{
									std::cout << split << ", ";
									Continent->getContinent().at(j)->addBoarders(prt);
									break;
								}
							}
						}
					}
				}
			}
			boarders.close();
			std::cout << endl;
		}
		std::cout << "-------------" << endl;
	}

	std::cout << "Set up done!" << endl;
}
Country* World::searchForCountry(string name)
{
	map<string, Country*>::iterator it = _territories.find(name);
	Country* retVal = it->second;

	return retVal;
}
World::~World()
{

}
bool World::isCountryAdjacent(Country* country1, Country* country2)
{
	for (int i = 0; i < country1->getBoarders().size(); i++)
	{
		if (country2->getName() == country1->getBoarders().at(i)->getName())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
vector<Country*> World::getAllAdjacentContries(Country* country)
{
	return country->getBoarders();
}

vector<Country*> World::AdjacentCountriesOwnedByPlayer(Player* player, Country* country)
{
	vector<Country*> returnVal;
	for (int i = 0; i < country->getBoarders().size(); i++)
	{
		if (country->getBoarders().at(i)->getOwner() == player->getPlayerName())
		{
			returnVal.push_back(country->getBoarders().at(i));
		}
	}
	return returnVal;
}
bool World::pathFindCountry(Country* country1, Country* country2, Player* player)
{
	cout << "DEbug country 1+++++++++++++++++++++++" << country1->getName() << endl;
	cout << "DEbug country 2+++++++++++++++++++++++" << country2->getName() << endl;

	if (country1->getName() == country2->getName() || isCountryAdjacent(country1, country2))
	{
		return true;
	}
	queue<Country*> countryQueue;
	vector<Country*> boardersToCountry1 = country1->getBoarders();
	countryQueue.push(country1);
	while (countryQueue.empty() == false)
	{
		Country* c = countryQueue.front();
		countryQueue.pop();
		if (c->getName() == country2->getName())
		{
			//need to put marked back to false for every country
			//here but map iterator is my enemy
			return true;
		}
		for (int i = 0; i < c->getBoarders().size(); i++)
		{
			vector<Country*> allBoardersToC = c->getBoarders();
			for (int k = 0; k < allBoardersToC.size(); k++)
			{
				for (int j = 0; j < player->getListCountriesOwned().size(); j++)
				{

					if (allBoardersToC.at(k)->getName() == player->getListCountriesOwned().at(j)->getName() && allBoardersToC.at(k)->marked == false)
					{
						countryQueue.push(allBoardersToC.at(k));
					}
				}
			}
		}
	}
	/*for (int i = 0; i < boardersToCountry1.size(); i++)
	{
	for (int j = 0; j < player->getListCountriesOwned().size(); j++)
	{

	if (boardersToCountry1.at(i)->getName() == player->getListCountriesOwned().at(j)->getName())
	{
	return pathFindCountry(boardersToCountry1.at(i), country2, player);
	}
	}
	}*/
}