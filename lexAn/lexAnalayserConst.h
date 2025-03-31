#pragma once
#include <cctype>
#include <string>
#include <fstream>
#include <iostream>


using namespace std;

enum alfabet {letter,EEE,dot,sign,endll,error=500,endll1,endll2,endll3};

enum states {q0,q1,q2,q3,q4,q5,q6,error1=1000,error2,error3,error4,error5,error6,error7};

const unsigned short alfabet_size = 5;
const unsigned short states_amount = 7;

class LAconst
{
	int val;

	typedef int(LAconst::* fptr)(const char ch);


	fptr s_table[states_amount][alfabet_size]; 


    double RCH ;
	int RS;
	int RP;
	bool RZ;

	int transliterator(char ch)
	{
		if (isdigit(ch)) return 0;

		if (ch == '+' || ch == '-') return 3;

		if (ch == '\n' || ch == '\0') return 4;

		switch (ch)
		{
		case 'E':
			return 1;
		case 'e':
			return 1;
		case '.':
			return 2;
		default:
			return 5;
		}
	}

	double POW(double a, int b)
	{ // b - число знаков после запятой
		if (b == 1) return a/10;
		if (b == 0) return a;
		if (b < 0)
		{
			for (int i = 0; i > b; i--)
				a *=10;
			return a;
		}
		if (b > 1)
		{
			for (int i = 1; i <= b; i++)
				a /= 10;
			return a;
		}
	}

	int p1(const char ch) { RCH += atoi(&ch); return q1; }
	int p2(const char ch) { RCH = 0; RS = 0; return q6; }
	int p3(const char ch) { RCH = RCH * 10 + atoi(&ch); return q1; }
	int p4(const char ch) { RS = 0; return q3; }
	int p5(const char ch) { RS = 0; return q2; }
	int p6(const char ch) { RCH = RCH * 10 + atoi(&ch); RS++; return q2; }
	int p7(const char ch) {  return q3; }
	int p8(const char ch) { RP = atoi(&ch); return q5; }
	int p9(const char ch) 
	{ if (ch == '-')RZ = 0; else if (ch == '+') RZ = 1; return q4; }
	int p10(const char ch) { RP = atoi(&ch); return q5; }
	int p11(const char ch) { RP = RP * 10 + atoi(&ch); return q5; }
	int p12(const char ch) { RCH = atoi(&ch); RS = 1; return q2; }

	int err1(const char ch) { return error1; }
	int err2(const char ch) { return error2; } // повторная точка 12..
	int err3(const char ch) { return error3; } // не там знак  1+2
	int err4(const char ch) { return error4; } // нет цифр после Е 12E
	int err5(const char ch) { return error5; } // пустое число 
	int err6(const char ch) { return error6; } // нет цыфр после знака 12.E+
	int err7(const char ch) { return error7; } // нет цыфр после . в начале числа   .E

	int end1(const char ch) { return endll1; }
	int end2(const char ch) { return endll2; }
	int end3(const char ch) { return endll3; }

public:
	LAconst()
	{
		val = 0;
		RCH = RP = RS = 0;
		RZ = 1;

		s_table[q0][letter] =	&LAconst::p1;
		s_table[q0][EEE] =		&LAconst::err1;
		s_table[q0][dot] =		&LAconst::p2;
		s_table[q0][sign] =		&LAconst::err1;
		s_table[q0][endll] =	&LAconst::err5;

		s_table[q1][letter] =	&LAconst::p3;
		s_table[q1][EEE] =		&LAconst::p4;
		s_table[q1][dot] =		&LAconst::p5;
		s_table[q1][sign] =		&LAconst::err1;
		s_table[q1][endll] =	&LAconst::end1;

		s_table[q2][letter] =	&LAconst::p6;
		s_table[q2][EEE] =		&LAconst::p7;
		s_table[q2][dot] =		&LAconst::err2;
		s_table[q2][sign] =		&LAconst::err1;
		s_table[q2][endll] =	&LAconst::end2;

		s_table[q3][letter] =	&LAconst::p8;
		s_table[q3][EEE] =		&LAconst::err1;
		s_table[q3][dot] =		&LAconst::err2;
		s_table[q3][sign] =		&LAconst::p9;
		s_table[q3][endll] =	&LAconst::err4;

		s_table[q4][letter] =	&LAconst::p10;
		s_table[q4][EEE] =		&LAconst::err1;
		s_table[q4][dot] =		&LAconst::err2;
		s_table[q4][sign] =		&LAconst::err1;
		s_table[q4][endll] =	&LAconst::err6;

		s_table[q5][letter] =	&LAconst::p11;
		s_table[q5][EEE] =		&LAconst::err1;
		s_table[q5][dot] =		&LAconst::err2;
		s_table[q5][sign] =		&LAconst::err1;
		s_table[q5][endll] =	&LAconst::end3;

		s_table[q6][letter] =	&LAconst::p12;
		s_table[q6][EEE] =		&LAconst::err1;
		s_table[q6][dot] =		&LAconst::err2;
		s_table[q6][sign] =		&LAconst::err1;
		s_table[q6][endll] =	&LAconst::err7;
	}

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
			RCH = RS = RP = 0;
			RZ = 1;
			val = 0;
			cout << "number: " << line << endl;
			bool res = parse(line);
			if (res)cout << "good\n"; else cout << "bad\n";
			cout << "------------------------------------------" << endl;
		}
		inputfile.close();
	}

	bool parse(const string strk)
	{

		int cur_state = q0;
		auto it = strk.begin();

		while (cur_state != endll1&&cur_state!=endll2&&cur_state!=endll3 && cur_state != error && cur_state != error1 && cur_state != error2 &&
			cur_state != error3 && cur_state != error4 && cur_state != error5 && cur_state != error6 && cur_state != error7)
		{
			if (it == strk.end())val = '\n';
			else val = *(it++);

			int t = transliterator(val);

			if (t == 5) cur_state = error1;
			else
				cur_state = (this->*s_table[cur_state][t])(val);

			RCH = RCH;
			RZ = RZ;
			RP = RP;
			RS = RS;

			int a = 0;

		}
		if (cur_state == error1) { cout << endl << "wrong input" << endl; return false; }
		if (cur_state == error2) { cout << endl << "second dot detected" << endl; return false;}
		if (cur_state == error3) { cout << endl << "wrong sign position" << endl;return false; }
		if (cur_state == error4) { cout << endl << "no digits after E" << endl;return false; }
		if (cur_state == error5) { cout << endl << "empty number" << endl; return false;}
		if (cur_state == error6) { cout << endl << "no digits after sign" << endl; return false;}
		if (cur_state == error7) { cout << endl << "no digits after dot with empty integer part" << endl; return false;}

		if (cur_state == endll1) { cout << endl << "number: " << RCH << endl; return true; }
		if (cur_state == endll2) { cout << endl << "number: "<<POW(RCH,RS) << endl; return true; }
		if (cur_state == endll3) { if (RZ) RS =RS - RP; else RS += RP;
		cout << endl << "number: "<<POW(RCH,RS) << endl; return true; }
	}

	
	


};






