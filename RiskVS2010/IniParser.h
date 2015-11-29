#ifndef INI_PARSER_H
#define INI_PARSER_H

#include <iostream>
#include <string>
#include <map>
#include <set>
using namespace std;

class IniParser
{
public:
	IniParser(string);
	set<string> getSectionsName();
	map<string, string> getSection(string);
	string getValueInSection(string section, string key);
	enum Exception
	{
		FILE_NOT_FOUND,
		FILE_UNREADABLE,
		MALFORMED_SECTION,
		MALFORMED_KEY_VALUE,
	};

private:
	map<string, map<string, string>> _sections;
};

#endif