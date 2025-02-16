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
			ERROR();
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
			ERROR();
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
		cout << "\nerror: net 0 posle 11\n"; 
	}

	void start(string s)
	{
		str = s;
		int size = str.size();
		for (int i = 0; i < size; i++)
		{
			(this->*q)(str[i]);
			cout << str[i] << endl;
		}
		if (q == &auto3::q2)
			cout << "bad" << endl;
		else cout << "good"<<endl;
	}

};