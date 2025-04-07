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

	int RI;     //регистр номера буквы в имени переменной

	int ROT;		//регистр отношения

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

	double* TO; //указатель на начало таблицы операндов 
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
		create_lexeme();
		RKL = arifmetic_operation;
		create_lexeme();
		q = q = &Lex_an::A2;
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
		create_lexeme();
		RKL = arifmetic_operation;
		create_lexeme();
		q = &Lex_an::A2;
	}

	void A2h() {
		RKL = l_bracket;
		create_lexeme();
		q = &Lex_an::A2;
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
		if (RZN != 1)
		{
			G1b();
			return;
		}
		create_lexeme();
		q = &Lex_an::A2;
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
		RKL = Lexeme_Class::TO;
		A2b();
		q = &Lex_an::A2;
	}

	void A3a() {
		RZN = (RZN + 1) * 26;
		aaa
	}

	void A3b() {
		RKL = r_bracket;
		create_lexeme();
		q = &Lex_an::A3;
	}

	void A3c()
	{
		create_lexeme();
		q = &Lex_an::A3;
	}

	void A3d() {
		DA1D();
		q = &Lex_an::A3;
	}

	void A3e() {
		DA2D();
		A3c();
		q = &Lex_an::A3;
	}

	void A3f() {
		DA3D();
		A3c();
		q = &Lex_an::A3;
	}

	void A3g() {
		DA1E();
		A3c();
		q = &Lex_an::A3;
	}

	void B1a() {
		// нужн таблица обнаружения
		⁘
	}

	void B1b() {
		create_lexeme();
		q = &Lex_an::B1;
	}

	void B1c() {
		DA3D();
		q = &Lex_an::B1;
	}

	void B1d() {
		ROB++;
		q = &Lex_an::B1;
	}

	void B1e() {
		create_lexeme();
		TL[NTL].LC = (Lexeme_Class)RKL;
		int rs = TS->Find(RSTR);
		if (rs==-1)
		{
			int insertion_pos = TS->el_add(RSTR, NTL);
			TL[NTL].value = insertion_pos;
			NTL++
		}
		q = &Lex_an::B1;
	}

	void C1a() {
		RKL = END;// конец цикла
		q = &Lex_an::C1;
	}

	void C2a() {
		RKL = operand;
		RI = RZN;
		q = &Lex_an::C2;
	}

	void C2b() {
		create_lexeme();
		RKL = operand;
		RI = RZN;
		q = &Lex_an::C2;
	}

	void C2d() {
		RI = RZN;
	}

	void D1a() {
		RKL = operand;
		RCH = RZN;
		q = &Lex_an::D1;
	}

	void D1b() {
		RCH *= 10;
		RCH += RZN;
		q = &Lex_an::D1;
	}

	void D1c() {
		create_lexeme();
		q = &Lex_an::D1;
	}

	void D2a() {
		RS++;
		RCH *= 10;
		RCH += RZN;
	}

	void D2b() {
		RS = 1;
		RCH = RZN;
		q = &Lex_an::D2;
	}

	void D2c() {
		RS = 0;
		q = &Lex_an::D2;
	}

	void D3a() {
		RS = 0;
		q = &Lex_an::D3;
	}

	void D4a() {
		if (RZN == plus_o) { RZ = 1; q = &Lex_an::D4; }
		if (RZN == minus_o) { RZ = 0; q = &Lex_an::D4; }
		G1b();
		
	}

	void D5a() {
		RZ = 1;
		q = &Lex_an::D5;
	}

	void D5b() {
		RP = RZN;
		q = &Lex_an::D5;
	}

	void D5c() {
		RP *= 10;
		RP += RZN;
		q = &Lex_an::D5;
	}

	void D6a() {
		create_lexeme();
	}

	void E1a() {
		RKL = GOTO;
		q = &Lex_an::E1;
	}

	void E1b() {
		RKL = GOSUB;
		q = q = &Lex_an::E1;
	}

	void E2a() {
		RSTR=RZN;
		q = &Lex_an::E2;
	}

	void E2b() {
		RSTR = RZN;
		q = &Lex_an::E2;
	}

	void E2c() {
		RSTR *= 10;
		RSTR += RZN;
		q = &Lex_an::E2;
	}

	void F1a() {
		RKL = LET;
		q = &Lex_an::F1;
	}

	void F1b() {
		RKL = FOR;
		q = &Lex_an::F1;
	}

	void F2a() {
		RI = RZN;
		q = &Lex_an::F2;
	}

	void F3a() {
		RI += RZN * 26;
		q = &Lex_an::F3;
	}

	void G1a() {
		RKL = REM;
		create_lexeme();
		q = &Lex_an::G1;
	}

	void G1b() {
		RKL = ERROR;
		create_lexeme();
		q = &Lex_an::G1;
	}

	void H1a() {
		RKL = RELATION;
		ROT = RZN;
		q = &Lex_an::H1;
	}

	void H1b() {
		create_lexeme();
		RKL = RELATION;
		ROT = RZN;
		q = &Lex_an::H1;
	}

	void H1c() {
		create_lexeme();
		RKL = RELATION;
		ROT = RZN;
		q = &Lex_an::H1;
	}

	void H1f() {
		H1b();
		RKL = RELATION;
		ROT = RZN;
		q = &Lex_an::H1;
	}

	void DA1D() {

	}

	void DA2D();

	void DA3D();

	void DA1E();

	void DA1Ecicle();
};