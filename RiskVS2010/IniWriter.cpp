#include "stdafx.h"
#include "IniWriter.h"
#include <fstream>

IniWriter::IniWriter(string fileName)
{
	_stream = new ofstream(fileName, ios::out);

	if (!_stream->is_open() || !_stream->good())
	{
		throw Exception::FILE_ACCESS_DENIED;
	}

	nbSection = 0;
}

void IniWriter::writeSectionKeyValuePair(string sectionName, map<string, string> keyValuePair)
{
	if (!_stream->good())
		throw Exception::FILE_UNWRITABLE;

	// separate sections with extra blank line
	if (nbSection > 0)
		*_stream << endl;

	// write section name
	*_stream << '['<<sectionName<<']' << endl;

	// write key-value pairs
	for (map<string, string>::iterator it = keyValuePair.begin(); it != keyValuePair.end(); ++it)
	{
		*_stream << it->first << '=' << it->second << endl;
	}

	nbSection++;
}

void IniWriter::writeSectionRaw(string sectionName, set<string> values)
{
	if (!_stream->good())
		throw Exception::FILE_UNWRITABLE;

	// separate sections with extra blank line
	if (nbSection > 0)
		*_stream << endl;

	// write section name
	*_stream << '['<<sectionName<<']' << endl;

	// write values
	for (set<string>::iterator it = values.begin(); it != values.end(); ++it)
	{
		*_stream << *it << endl;
	}

	nbSection++;
}

void IniWriter::writeSectionRaw(string sectionName, map<string, set<string>> values)
{
	if (!_stream->good())
		throw Exception::FILE_UNWRITABLE;

	// separate sections with extra blank line
	if (nbSection > 0)
		*_stream << endl;

	// write section name
	*_stream << '['<<sectionName<<']' << endl;

	// write values
	for (map<string, set<string>>::iterator it = values.begin();it != values.end(); ++it)
	{
		set<string> values2 = it->second;
		for (set<string>::iterator it2 = values2.begin(); it2 != values2.end(); ++it2)
		{
			*_stream << *it2 << endl;
		}
		*_stream << endl;
	}

	nbSection++;
}

void IniWriter::close()
{
	if (_stream->good())
		_stream->close();
}

IniWriter::~IniWriter()
{
	this->close();
	delete _stream;
}
