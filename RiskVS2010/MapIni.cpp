#include "stdafx.h"
#include "MapIni.h"
#include "Country.h"
#include "Player.h"
#include "IniWriter.h"

using namespace std;



MapIni::MapIni(map<string, Continent*> continents, map<string, Country*> countries)
{
	_continents = continents;
	_territories = countries;
}

MapIni::MapIni(string fileName)
{
	_parser = NULL;

	try
	{
		_parser = new IniParser(fileName);
	}
	catch (IniParser::Exception e)
	{
		switch (e)
		{
		case IniParser::Exception::FILE_NOT_FOUND:
			cout << "Error: The parser could not open the file " << fileName << endl;
			throw;
		case IniParser::Exception::FILE_UNREADABLE:
			cout << "Error: The parser was unable to read the file " << fileName << endl;
			throw;
		case IniParser::Exception::MALFORMED_SECTION:
			cout << "Error: The file " << fileName << " contains malformed sections" << endl;
			throw;
		case IniParser::Exception::MALFORMED_KEY_VALUE:
			cout << "Error: The file " << fileName << " contains malformed key-value pairs" << endl;
			throw;
		}
	}

	readMapInfo();
	readContinents();
	readTerritories();

	delete _parser;
}

void MapIni::readMapInfo()
{
	//check for Map section
	set<string> sectionNames = _parser->getSectionsName();
	if (sectionNames.find("Map") == sectionNames.end())
	{
		cout << "The configuration file lacks a Map section" << endl;
		throw;
	}

	// copy as is
	_mapInfo = _parser->getSection("Map");
}

void MapIni::readContinents()
{
	//check for Continents section
	set<string> sectionNames = _parser->getSectionsName();
	if (sectionNames.find("Continents") == sectionNames.end())
	{
		cout << "The configuration file lacks a Continents section" << endl;
		throw;
	}

	map<string, string> continents = _parser->getSection("Continents");

	// create continent objects
	for (map<string, string>::iterator it = continents.begin(); it != continents.end(); ++it)
	{
		Continent *newContinent = new Continent(it->first, atoi(it->second.c_str()));
		_continents[it->first] = newContinent;
	}
}

void MapIni::readTerritories()
{
	//check for Territories section
	set<string> sectionNames = _parser->getSectionsName();
	if (sectionNames.find("Territories") == sectionNames.end())
	{
		cout << "The configuration file lacks a Territories section" << endl;
		throw;
	}

	map<string, string> territories = _parser->getSection("Territories");

	// create territories objects
	for (map<string, string>::iterator it = territories.begin(); it != territories.end(); ++it)
	{
		string name, continent;
		int posX, posY;
		list<string> adj;
		
		// parse line
		istringstream iss(it->second);
		int i=0;
		for (string token; getline(iss, token, ','); i++)
		{
			switch (i)
			{
			case 0:
				name = move(token);
				break;
			case 1:
				posX = atoi(token.c_str());
				break;
			case 2:
				posY = atoi(token.c_str());
				break;
			case 3:
				continent = move(token);
				break;
			default:
				adj.push_back(token);
				break;
			}
		}

		// check if territory name doesn't already exist
		if (_territories.find(name) != _territories.end())
		{
			cout << "Territory " << name << " is declared twice!" << endl;
			throw;
		}

		// create new territory
		Country* newTerr = new Country(name, posX, posY);
		//for (string::size_type i=0; i<adj.size(); i++)
		//	newTerr->addAdjacentTerritory(adj[i]);
		_adjacentTerritories[name] = adj;

		// check if territory belongs to existing continents, and add it
		if (_continents.find(continent) != _continents.end())
		{
			_continents[continent]->addTerritory(newTerr);
		} else {
			cout << "Country " << name << " belong to unknown continent " << continent << endl;
			throw;
		}
		
		// save
		_territories[name] = newTerr;
		//newTerr->print();

	} //iterator over territories
}

vector<Country*> getAdjacentCountriesOfOtherPlayers(Country* country, Player& player)
{
	vector<Country*> adjacent;

	// TODO DANNY

	return adjacent;
}

Country* MapIni::getCountry(string name)
{
	for (map<string, Country*>::iterator it = _territories.begin(); it != _territories.end(); ++it)
	{
		if (it->second->getName() == name)
		{
			return it->second;
		}
	}

	return NULL;
}


map<string, string> MapIni::getMapInfo()
{
	return _mapInfo;
}

map<string, Continent*> MapIni::getContinents()
{
	return _continents;
}

map<string, Country*> MapIni::getTerritories()
{
	return _territories;
}

map<string, list<string>> MapIni::getAdjacency()
{
	return _adjacentTerritories;
}

bool MapIni::writeMapToFile(map<string, string> mapInfo,string fileName)
{
	bool success = true;
	
	// VALIDATION
	for (map<string, Country*>::iterator it = _territories.begin(); it != _territories.end(); ++it)
	{
		bool isAssigned = false;
		for (map<string, Continent*>::iterator it2 = _continents.begin(); it2 != _continents.end(); ++it2)
		{
			if (it2->second->isInContinent(it->second)) {
				isAssigned = true;
				break;
			}
		}

		if (!isAssigned) {
			cout << "There are errors on the map. Make sure all Countries are assigned to a Continent." << endl;
			return false;  //Found a Country that is not assigned to a continent: Map is invalid
		}
	}

	map<string, string> continentsDesc;
	map<string, set<string>> territoriesDescByContinent;

	// prepare continents
	for (map<string, Continent*>::iterator it = _continents.begin(); it != _continents.end(); ++it)
	{
		continentsDesc[it->first] = to_string(it->second->getBonus());

		// prepare territories
		vector<Country*> territories = it->second->getTerritories();
		for (vector<Country*>::size_type i=0; i<territories.size(); i++)
		{
			ostringstream os;
			os << territories[i]->getName() << ","
				<< territories[i]->getX() << ","
				<< territories[i]->getY() << ","
				<< it->first;

			vector<Country*> adjTerr = territories[i]->getAdjacentTerritories();
			for (vector<Country*>::size_type j=0; j<adjTerr.size(); j++)
			{
				os << "," << adjTerr[j]->getName();
			}
			territoriesDescByContinent[it->first].insert(os.str());
		}
	}

	try
	{
		IniWriter writer(fileName);
		
		// write Map section
		writer.writeSectionKeyValuePair("Map", mapInfo);

		// write Continents
		writer.writeSectionKeyValuePair("Continents", continentsDesc);

		// write Territories
		writer.writeSectionRaw("Territories" , territoriesDescByContinent);

		// close file
		writer.close();
	} catch (IniWriter::Exception e)
	{
		switch (e)
		{
		case IniWriter::Exception::FILE_ACCESS_DENIED:
			cout << "Error: Could not open the file " << fileName << " for writing." << endl;
			throw;
		case IniWriter::Exception::FILE_UNWRITABLE:
			cout << "Error: Something occurred while writing to the file " << fileName << endl;
			throw;
		}
	}

	return success;
}

bool MapIni::writeWorldToFile(World world, string fileName)
{
	return MapIni::writeMapToFile(world.getInfo(), fileName);
}

MapIni::~MapIni(void)
{
	// assume caller will delete continents and territories
}
