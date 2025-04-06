#pragma once

#include <vector>
#include <fstream>

#include "strTable.h"

using namespace std;


enum Lexeme_Class {lable=1,operand,arifmetic_operation,RELATION,NEXT,LET,FOR,GOTO,GOSUB,l_bracket,r_bracket,IF,RETURN,END,TO,STEP,REM,ERROR,ENDF};
enum operation {plus_o=1,minus_o,mult_o,div_o,exponenciation_o};
enum relation {EQ=1,LESS,GREATER,LEQ,GREQ,NOTEQ};

enum simbolic_class{ letter,digit,arifmetic_op,relation,l_br,r_br,dot,space,endln,endf,errors};

struct Lexeme
{
	Lexeme_Class LC;
	int value;

};


class Lex_an
{
	simbolic_class translit(char ch);

	void Error_handler(int N_str, string err_msg);

	void create_lexeme();

	int RSTR;	//регистр строки

	bool RZ;    //регистр знака

	int RCH;	//регистр числа

	int RP;		//регистр порядка

	int RS;		//регистр счетчика

	int NTS;	//указатель на 1й свободный элемент в TS в обл переполнения

	int NTO;	//указ на первый свобод элем в 

	int NTL;	//указ на первый свобод элем в таблице лексем

	int RKL;	//регистр класа лексем

	int RZN;	//регистр значения символа

	int RSOS;	//регистр состояния

	int ROB;	//регистр обнаружения

	int RK;		//регистр входного символа

	int RSE;	//реристр счетчика ошибок

	Lexeme* TL;	//указатель на начело таблицы лексем

	double* TO;  //указатель на начало таблицы операндов 
//где то 500 эл
	Hash* TS;	//указатель на начало таблицы строк

	void(Lex_an::* q)();

public:

	Lex_an();

	~Lex_an();

	void print();

	void start(string file_name); // построчно читаем

	void A1();

	void A2();

	void A3();

	void B1();

	void C1();

	void C2();

	void D1();

	void D2();

	void D3();

	void D4();

	void D5();

	void D6();

	void E1();

	void E2();

	void F1();

	void F2();

	void F3();

	void G1();

	void H1();

	void M1();

	void M2();

	void M3();

	void Exit1();

	void Exit2();

	void Exit3();

	void Exit4();

	void Exit5();


	void A1a() {
		create_lexeme();
		q = &Lex_an::A1;
	}

	void A1b() {
		DA1D();
		q = &Lex_an::A1;
	}

	void A1c() {
		DA2D();
		A1a();
	}

	void A1d() {
		DA3D();
		A1a();
	}

	void A1e() {
		DA1E();
		A1a();
	}

	void A2a() {
		RKL = arifmetic_operation;
		q = &Lex_an::A2;
	}

	void A2b() {
		create_lexeme();
		q = &Lex_an::A2;
	}

	void A2c() {
		aaaa
	}

	void A2d() {
		DA2D();
		A2g();
		q = &Lex_an::A2;
	}

	void A2e() {
		DA3D();
		q = &Lex_an::A2;
	}

	void A2f() {
		DA1E();
		q = &Lex_an::A2;
	}

	void A2g() {
		aaa
	}

	void A2h() {
		aaa
	}

	void A2i() {
		aaa
	}

	void A2j() {
		DA1E;
		q = &Lex_an::A2;
	}

	void A2k() {
		create_lexeme();
		q = &Lex_an::A2;
	}

	void A2l() {
		DA1D();
		A2k();
		q = &Lex_an::A2;
	}

	void A2m() {
		DA2D();
		A2k();
		q = &Lex_an::A2;
	}

	void A2n() {
		DA3D();
		A2l();
		q = &Lex_an::A2;
	}

	void A2o() {
		if (RZN != 1) Error_handler(RSTR,"aaa"); else A2b();aaa
	}

	void A2p() { // нужна таблица с двойными операторами отношений
		int r = 
	}

	void A2q() {
		RKL = ENDF;
		A2b();
	}

	void A2r() {
		RKL = IF;
		A2b();
	}

	void A2s() {
		RKL = RETURN;
		A2b();
	}

	void A2t() {
		RKL = STEP;
		A2b();
	}

	void A2u() {
		aaa
	}

	void A3a() {
		RZN = (RZN + 1) * 26;
		
	}

	void A3b();

	void A3c();

	void A3d();

	void A3e();

	void A3f();

	void A3g();

	void B1a();

	void B1b();

	void B1c();

	void B1d();

	void B1e();

	void C1a();

	void C1b();

	void C1c();

	void C1d();

	void C2a();

	void C2b();

	void C2c();

	void C2d();

	void D1a();

	void D1b();

	void D1c();

	void D2a();

	void D2b();

	void D2c();

	void D3a();

	void D3b();

	void D3c();

	void D4a();

	void D5a();

	void D5b();

	void D5c();

	void D6a();

	void E1a();

	void E1b();

	void E1c();

	void E2a();

	void E2b();

	void E2c();

	void F1a();

	void F1b();

	void F2a();

	void F3a();

	void G1a();

	void G1b();

	void H1a();

	void H1b();

	void H1c();

	void H1d();

	void H1e();

	void H1f();

	void DA1D();

	void DA2D();

	void DA3D();

	void DA1E();

	void DA1Ecicle();
};