#pragma once

#include <string>
#include <iostream>
#include "auto_base.h"

using namespace std;

class auto4 :public base
{
	void(auto4::* q)(char ch);
public:

	auto4()
	{
		q = &auto4::q0;
	}

	void q0(char ch)
	{
		switch (ch)
		{
		case '1':
			q = &auto4::q1;
			break;
		case '0':
			q = &auto4::q1;
			break;
		default:
			q = &auto4::ERROR;

		}
	}

	void q1(char ch)
	{
		switch (ch)
		{
		case '0':
			q = &auto4::q2;
			break;
		case '1':
			q = &auto4::q2;
			break;
		default:
			q = &auto4::ERROR;

		}

	}

	void q2(char ch)
	{
		switch (ch)
		{
		case '0':
			q = &auto4::ERROR1;

			break;
		case '1':
			q = &auto4::q0;
			break;
		default:
			q = &auto4::ERROR;

		}
	}

	void ERROR(char ch)
	{
		cout << "\nerror symbol\n"; 
	}

	void ERROR1(char ch)
	{
		cout << "\nerror: ne 1 na 3ei pozitcii\nbad"; 
	}

	bool start(string s)
	{
		q = &auto4::q0;
		str = s;
		int size = str.size();
		for (int i = 0; i < size; i++)
		{
			(this->*q)(str[i]);
			cout << str[i] << endl;
			if (q == &auto4::ERROR) { ERROR(str[i]); break; }
			if (q == &auto4::ERROR1) { ERROR1(str[i]); break; }
		}
		if (q == &auto4::ERROR || q == &auto4::ERROR1) { return false; }
		else return true;
	}
};