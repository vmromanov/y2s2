#pragma once

#include <vector>
#include <fstream>

#include "lexAnalayserConst.h"
#include "strTable.h" 
 
using namespace std;


enum Lexeme_Class {lable=1,operand,arifmetic_operation,relation,NEXT,LET,FOR,GOTO,GOSUB,l_bracket,r_bracket,IF,RETURN,END,TO,STEP,REM,ERROR,ENDF};
enum operation {plus=1,minus,mult,div,exponenciation};
enum relation {EQ=1,LESS,GREATER,LEQ,GREQ,NOTEQ};

enum simbolic_class{digit,};

struct Lexeme
{
	Lexeme_Class LC;
	int value;

};


class Lex_an
{
	int translit(char ch);

	vector<Lexeme> Lexeme_table;

	vector<double> TO;

	Hash TS;

	void(Lex_an::* q)(char ch);

public:

	Lex_an();

	~Lex_an();

	void create_lexeme();

	void print();

	void Error_handler(int N_str, string err_msg);

	void A1(char ch);

	void A2(char ch);

	void A3(char ch);

	void B1(char ch);

	void C1(char ch);

	void C2(char ch);

	void D1(char ch);

	void D2(char ch);

	void D3(char ch);

	void D4(char ch);

	void D5(char ch);

	void D6(char ch);

	void E1(char ch);

	void E2(char ch);

	void F1(char ch);

	void F2(char ch);

	void F3(char ch);

	void G1(char ch);

	void H1(char ch);

	void M1(char ch);

	void M2(char ch);

	void M3(char ch);

	void Exit1(char ch);

	void Exit2(char ch);

	void Exit3(char ch);

	void Exit4(char ch);

	void Exit5(char ch);

};