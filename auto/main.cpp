#include <string>
#include <iostream>

using namespace  std;

//enum states { Q0, Q1, Q2, Q3 };

class base
{
protected:
	string str;

public:
	virtual void start(string str) = 0;

	virtual ~base() {};
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
		case '0':
			q = &auto1::q2;
			break;
		case '1':
			q = &auto1::q1;
			break;
		default:
			ERROR();

		}
	}

	void q1(char ch)
	{
		cout << "q1 work\n";
		switch(ch)
		{
		case '0':
			ERROR1();
			break;
		case '1':
			q = &auto1::q0;
			break;
		default:
			ERROR();
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
			ERROR();
			break;
		default: ERROR();
		}
		
	}

	void q3(char ch)
	{
		cout << "q3 work\n";
		switch (ch)
		{
		case '1':
			ERROR();
			break;
		case '0':
			q = &auto1::q2;
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
		cout << "error: 0 - chetno";
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
		if (q == &auto1::q2)
			cout << "good" << endl;
		else cout << "bad" << endl;
	}
};

int main()
{
	auto1 b;
	b.start("1111000");
	return 0;
}
