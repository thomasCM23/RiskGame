#include "stdafx.h"
#include "IniParser.h"
#include <fstream>

/** INI-like file parser
  * Algorithm taken from the Boost library
  */
IniParser::IniParser(string fileName)
{
	string line;
	ifstream stream(fileName);

	if (!stream.is_open() || !stream.good())
	{
		throw Exception::FILE_NOT_FOUND;
	}

    // read all lines
	map<string, string> *currentSection = NULL;
    while (stream.good())
    {
		getline(stream, line);
		if (!stream.good() && !stream.eof())
			throw Exception::FILE_UNREADABLE;
		
		// if line is non-empty (sensitive to whitespace)
		if (!line.empty())
		{
			// check whether start of a section
			if (line[0] == '[')
			{
				// check for closing bracket
				string::size_type endPos = line.find(']');
				if (endPos == string::npos)
					throw Exception::MALFORMED_SECTION;

				string sectionName = line.substr(1, endPos-1);

				// check if section is already declared
				if (_sections.find(sectionName) != _sections.end())
					throw Exception::MALFORMED_SECTION;
				
				// create new section
				_sections[sectionName];

				// set current section
				currentSection = &(_sections)[sectionName];
			}
			else // content of section
			{
				// key-value not in a section
				if (currentSection == NULL)
					throw Exception::MALFORMED_SECTION;
				
				string::size_type eqPos = line.find('=');

				// check if "=" sign is found
				string key, data;
				if (eqPos == string::npos || eqPos == 0)
				{
					//throw Exception::MALFORMED_KEY_VALUE;
					// check if key already declared within section
					if (currentSection->find(line) != currentSection->end())
						throw Exception::MALFORMED_KEY_VALUE;

					key = line;
					data = line;
				} else {

					key = line.substr(0, eqPos);
					data = line.substr(eqPos + 1, string::npos);
				
					// check if key already declared within section
					if (currentSection->find(key) != currentSection->end())
						throw Exception::MALFORMED_KEY_VALUE;
				}
				// add key value pair to section
				(*currentSection)[key] = data;
            } // line type
        } // non-empty line
	} // reading stream

	stream.close();
}

set<string> IniParser::getSectionsName()
{
	set<string> sectionsName;
	for (map<string, map<string, string>>::iterator it = _sections.begin(); it != _sections.end(); ++it)
	{
		sectionsName.insert(it->first);
	}
	return sectionsName;
}

map<string, string> IniParser::getSection(string sectionName)
{
	return _sections[sectionName];
}

string IniParser::getValueInSection(string section, string key)
{
	if (_sections.find(section) != _sections.end()
		&& _sections[section].find(key) != _sections[section].end())
	{
		return _sections[section][key];
	}
	return "";
}
