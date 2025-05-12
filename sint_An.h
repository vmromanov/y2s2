#pragma once
#include <stack>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "Lexical_Analyzer.h"
using namespace std;

enum atom_class { ENDING, NUMSTR, LET, GOTO, GOSUB, RETURN, IFGO, CAP, LABEL, INC, ADD, SUB, MULT, DIV, EXP, PLUS, MINUS };

struct el_atom
{
	int type;			//класс
	int a1, a2, a3, a4;	// атрибуты
};
 
class Sint_An:public Lexical_analyzer
{
	typedef void (Sint_An::* pfnk)();

	vector<el_atom> TA;
	int NTA = 0;				// индекс первого свободного элемента в TA

	int i;						// индекс для таблицы лексем

	stack<int> st;

	int msmb;					//символ магазина

	int NSTR;					//номер текущей строки

	pfnk T[33][23];




	void add_atom(int type, int a1, int a2 = -1, int a3 = -1, int a4 = -1); // хоть 1 параметр должен быть



public: 
	Sint_An();

	void f1();
	void f2();
	void f3();
	void f4();
	void f5();
	void f6();
	void f7();
	void f8();
	void f9();
	void f11();
	void f12();
	void f13();
	void f14();
	void f15();
	void f16();
	void f17();
	void f18();
	void f19();
	void f20();
	void f21();
	void f22();
	void f23();
	void f24();
	void f25();
	void f26();
	void f27();
	void f28();
	void a();
	void b();
	void c();
	void d();
	void e();
	void f();
	void g();
	void h();
	void i();
	void j();
	void k();
	void l();
	void m();
	void n();
	void o();
	void p();
	void q();
	void r();
	void start(char* fname);

	void A();
	void B();
	void G1();
	void G2();
	void C();
	void D();
	void K1();
	void K2();
	void K3();
	void K4();
	void K5();
	void K6();
	void K7();
	void E1();
	void E2();
	void E3();
	void L();
	void M1();
	void M2();
	void M3();
	void M4();
	void H1();
	void H2();
	void K();
	void P1();
	void P2();
	void P3();
	void P4();
	void P();
	void T1();
	void T2();
	void T3();
	void O();
	
};
