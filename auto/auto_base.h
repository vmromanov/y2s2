#pragma once
#include <string>

using namespace std;

class base
{
protected:
	string str;

public:
	virtual void start(string str) = 0;

	virtual ~base() {};
};