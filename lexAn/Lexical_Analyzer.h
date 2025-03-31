#pragma once

#include <vector>
#include <fstream>

#include "lexAnalayserConst.h"
#include "strTable.h" 
 
using namespace std;


enum Lexeme_Class {lable=1,operand,arifmetic_operation,RELATION,NEXT,LET,FOR,GOTO,GOSUB,l_bracket,r_bracket,IF,RETURN,END,TO,STEP,REM,ERROR,ENDF};
enum operation {plus=1,minus,mult,div,exponenciation};
enum relation {EQ=1,LESS,GREATER,LEQ,GREQ,NOTEQ};

enum simbolic_class{ letter,digit,arifmetic_op,relation,l_br,r_br,dot,space,endln,endf,error};

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

	string RSTR;	//регистр строки

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

};