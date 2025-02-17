#pragma once

#include <iostream>
#include <fstream>

enum alfabet{zero,One1,ln};

enum states{begin,error,end};

const unsigned alfabet_size = 3;

using namespace std;

class Machine
{
protected:
	int val = 0;
	int Begin() { return states::begin; }
	int ERROR() { return states::error; }
	int End() { return states::end; }
	int transliterator(int ch)
	{
		if (ch == '0') return zero;
		else if (ch == '1') return One1;
		else if (ch == '\n'||ch=='\0') return ln;
		else return -1;
	}

	

public:
	virtual bool parse(const string strk) = 0;

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
			bool res=parse(line);
			if (res)cout << "good\n"; else cout << "bad\n";
			cout << "------------------------------------------" << endl;
		}
		inputfile.close();
	}
};