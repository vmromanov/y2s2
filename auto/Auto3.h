#pragma once

#include <string>
#include <iostream>
#include "auto_base.h"

using namespace std;


class auto3 :public base
{
	void(auto3::* q)(char ch);
public:

	auto3()
	{
		q = &auto3::q0;
	}

	void q0(char ch)
	{
		switch (ch)
		{
		case '1':
			q = &auto3::q1;
			break;
		case '0':
			q = &auto3::q0;
			break;
		default:
			q = &auto3::ERROR;

		}
	}

	void q1(char ch)
	{
		switch (ch)
		{
		case '0':
			q = &auto3::q0;
			break;
		case '1':
			q = &auto3::q2;
			break;
		default:
			q = &auto3::ERROR;
		}

	}

	void q2(char ch)
	{
		switch (ch)
		{
		case '0':
			q = &auto3::q0;
			break;
		case '1':
			q = &auto3::ERROR1;
			break;
		default:
			q = &auto3::ERROR;
		}
	}

	void ERROR(char ch)
	{
		cout << "\nerror symbol: "<<ch<<endl;
	}

	void ERROR1(char ch)
	{
		cout << "\nerror: net 0 posle 11\n"; 
	}

	bool start(string s)
	{
		q = &auto3::q0;
		str = s;
		int size = str.size();
		for (int i = 0; i < size; i++)
		{
			(this->*q)(str[i]);
			cout << str[i] << endl;
			if (q == &auto3::ERROR) { ERROR(str[i]); break; }
			if (q == &auto3::ERROR1) { ERROR1(str[i]); break; }
		}
		if (q == &auto3::q2)
			return false;
		else return true;
	}

};