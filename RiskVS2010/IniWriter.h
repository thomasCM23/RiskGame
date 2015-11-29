#ifndef INI_WRITER_H
#define INI_WRITER_H

#include <iostream>
#include <string>
#include <map>
#include <set>
using namespace std;

class IniWriter
{
public:
	IniWriter(string);
	void writeSectionKeyValuePair(string, map<string, string>);
	void writeSectionRaw(string, set<string>);
	void writeSectionRaw(string, map<string, set<string>>);
	void close();
	~IniWriter(void);
	enum Exception
	{
		FILE_ACCESS_DENIED,
		FILE_UNWRITABLE,
	};

private:
	ofstream* _stream;
	unsigned int nbSection;
};

#endif