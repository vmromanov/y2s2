#pragma once
#include <string>
#include <iostream>
#include "auto_base.h"


using namespace std;

class auto1 :public base
{
	void(auto1::* q)(char ch);

public:
	auto1()
	{
		q = &auto1::q0;
	}

	void q0(char ch)
	{
		cout << "q0 work\n";
		switch (ch)
		{
		case '0':
			q = &auto1::q2;
			break;
		case '1':
			q = &auto1::q1;
			break;
		default:
			q = &auto1::ERROR;

		}
	}

	void q1(char ch)
	{
		cout << "q1 work\n";
		switch (ch)
		{
		case '0':
			q = &auto1::ERROR;
			break;
		case '1':
			q = &auto1::q0;
			break;
		default:
			q = &auto1::ERROR;
		}
	}

	void q2(char ch)
	{
		cout << "q2 work\n";
		switch (ch)
		{
		case '0':
			q = &auto1::q3;
			break;
		case '1':
			q = &auto1::ERROR;
			break;
		default: q = &auto1::ERROR;
		}

	}

	void q3(char ch)
	{
		cout << "q3 work\n";
		switch (ch)
		{
		case '1':
			q = &auto1::ERROR;
			break;
		case '0':
			q = &auto1::q2;
			break;
		default:
			q = &auto1::ERROR;
		}
	}

	void ERROR(char ch)
	{
		cout << "\nerror symbol\n";
	}

	void ERROR1(char ch)
	{
		cout << "\nnechet 1\n";
	}

	void ERROR2(char ch)
	{
		cout << "\nchetno 0\n";
	}

	bool start(string s)
	{
		str = s;
		int size = str.size();
		for (int i = 0; i < size; i++)
		{
			(this->*q)(str[i]);
			cout << str[i] << endl;
			if (q == &auto1::ERROR) break;
		}
		if (q == &auto1::q2)
			return true;
		else return false;
	}
};