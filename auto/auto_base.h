#pragma once
#include <string>
#include <fstream>
using namespace std;

class base
{
protected:
	string str;

public:
	virtual bool start(string str) = 0;

	virtual ~base() {};

	void readinfile(string str)
	{
		ifstream inputfile(str);
		if (!inputfile.is_open())
		{
			cout << "unable to open file";
			return;
		}
		string line;
		while (inputfile >> line)
		{
			cout << "chain: " << line << endl;
			bool res = start(line);
			if (res)cout << "good\n"; else cout << "bad\n";
			cout << "------------------------------------------" << endl;
		}
		inputfile.close();
	}

};