#pragma once

#include <string>
#include <iostream>
#include "auto_base.h"

using namespace std;

class auto2:public base
{
	void(auto2::* q)(char ch);

public:

	auto2()
	{
		q = &auto2::q0;
	}

	void q0(char ch)
	{
		switch (ch)
		{
		case '1':
			q = &auto2::q1;
			break;
		case '0':
			q = &auto2::q0;
			break;
		default:
			ERROR();
		}
	}

	void q1(char ch)
	{
		switch (ch)
		{
		case '0':
			q = &auto2::q2;
			break;
		case '1':
			q = &auto2::q1;
			break;
		default:
			ERROR();
		}

	}

	void q2(char ch)
	{
		switch (ch)
		{
		case '0':
			q = &auto2::q1;
			break;
		case '1':
			ERROR1();
			break;
		default:
			ERROR();
		}
	}

	void ERROR()
	{
		cout << "\nerror symbol\n"; exit(1);
	}

	void ERROR1()
	{
		cout << "\nerror 0 - nechetno\nbad\n"; exit(1);
	}

	void start(string s)
	{
		auto2::str = s;
		int size = str.size();
		for (int i = 0; i < size; i++)
		{
			(this->*q)(str[i]);
			cout << str[i] << endl;
		}
		cout << "good" << endl;
	}
};