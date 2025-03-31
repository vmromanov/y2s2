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

	string RSTR;	//������� ������

	bool RZ;    //������� �����

	int RCH;	//������� �����

	int RP;		//������� �������

	int RS;		//������� ��������

	int NTS;	//��������� �� 1� ��������� ������� � TS � ��� ������������

	int NTO;	//���� �� ������ ������ ���� � 

	int NTL;	//���� �� ������ ������ ���� � ������� ������

	int RKL;	//������� ����� ������

	int RZN;	//������� �������� �������

	int RSOS;	//������� ���������

	int ROB;	//������� �����������

	int RK;		//������� �������� �������

	int RSE;	//������� �������� ������

	Lexeme* TL;	//��������� �� ������ ������� ������

	double* TO;  //��������� �� ������ ������� ��������� 
//��� �� 500 ��
	Hash* TS;	//��������� �� ������ ������� �����

	void(Lex_an::* q)();

public:

	Lex_an();

	~Lex_an();

	void print();

	void start(string file_name); // ��������� ������

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