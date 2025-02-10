#include <string>
#include <iostream>

using namespace  std;

//enum states { Q0, Q1, Q2, Q3 };

class base
{
protected:
	string s;

public:
	virtual void start(string s = 0);

	virtual ~base();
};

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
		case 0:
			q = &auto1::q2;
			break;
		case 1:
			q = &auto1::q1;
			break;
		default:
			ERROR();

		}
	}

	void q1(char ch)
	{
		switch(ch)
		{
		case 0:
			ERROR();
			break;
		case 1:
			q = &auto1::q0;
			break;
		default:
			ERROR();
		}
	}

	void q2(char ch)
	{
		switch (ch)
		{
		case 0:
			q = &auto1::q3;
			break;
		case 1:
			ERROR();
			break;
		}
	}

	void q3(char ch)
	{
		switch (ch)
		{
		case 1:


		case 0:
		}
	}

};

