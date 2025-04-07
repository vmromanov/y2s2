#include "Lexical_Analyzer.h"

simbolic_class Lex_an::translit(char ch)
{
	if (isalpha(ch)) {
		RZN = tolower(ch) - 'a' + 1; return letter;
	}
	if (isdigit(ch))
	{
		RZN = ch - '0'; return digit;
	}
	if (ch == '<' || ch == '>' || ch == '=') { 
		if (ch == '=')RZN = 1; if (ch == '<') RZN = 2; else RZN = 3; return relation; }
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
		if (ch == '+')RZN = 1; if (ch == '-')RZN = 2; if (ch == '*')RZN = 3; if (ch == '/')RZN = 4; if (ch == '^')RZN = 5; return arifmetic_op;
	}
	if (ch == '(') { return l_br; }
	if (ch == ')') return r_br;
	if (ch == ' ' || ch == '\t') return space;
	if (ch == '.') return dot;
	if (ch == '\n') return endln;
	return errors;
}// потом RK  = translit...

void Lex_an::create_lexeme()
{
	Lexeme L;
	L.LC = RKL;

}

void Lex_an::A1()
{
	switch (RK)
	{
	case digit:
		E2a();
		break;
	case space:
		break;
	case endln:
		break;
	case endf:
		Exit1(); 
		break;
	default:
		RSE++;
		G1b();
	}
}

void Lex_an::A2()
{
	switch (RK)
	{
	case letter:
		C2a();
		break;
	case digit:
		D1a();
		break;
	case arifmetic_op:
		A2a();
		break;
	case relation:
		H1a();
		break;
	case l_br:
		A2h();
		break;
	case r_br:
		A3b();
		break;
	case dot:
		q = &Lex_an::D6;
		break;
	case space:
		break;
	case endln:
		q = &Lex_an::A1;
		break;
	case endf:
		Exit1();
		break;
	default:
		G1b(); // регистр класа лексемы - ошибка, создать лексему,q=G1
	}
}

void Lex_an::A3()
{
	switch (RK)
	{
	case letter:
		B1a();
		break;
	case digit:
		D1a();
		break;
	case arifmetic_op:
		A2a();
		break;
	case relation:
		H1a();
		break;
	case l_br:
		A2h();
		break;
	case r_br:
		A3b();
		break;
	case dot:
		q = &Lex_an::D6;
		break;
	case space:
		break;
	case endln:
		q = &Lex_an::A1;
		break;
	case endf:
		Exit1();
		break;
	default:
		G1b();
	}
}

void Lex_an::B1()
{
	switch (RK)
	{
	case letter:
		q= &Lex_an::M1;
		break;
	case space:
		q = &Lex_an::B1;
		break;
	default:
		G1b();
	}
}

void Lex_an::C1()
{
	switch (RK)
	{
	case letter:
		C2d();
		break;
	case space:
		break;
	case endf:
		Exit3();
		break;
	default:
		G1b();
	}
}

void Lex_an::C2()
{
	switch (RK)
	{
	case letter:
		B1b();
		break;
	case digit:
		A3a();
		break;
	case arifmetic_op:
		A2g();
		break;
	case relation:
		H1b();
		break;
	case l_br:
		A2k();
		break;
	case r_br:
		A3c();
		break;
	case space:
		break;
	case endln:
		A1a();
		break;
	case endf:
		Exit4();
		break;
	default:
		G1b();
	}
}

void Lex_an::D1()
{
	switch (RK)
	{
	case letter:
		q = &Lex_an::M2;
		break;
	case digit:
		D1b();
		break;
	case arifmetic_op:
		A2c();
		break;
	case relation:
		H1c();
		break;
	case l_br:
		A2l();
		break;
	case r_br:
		A3d();
		break;
	case dot:
		D2c();
		break;
	case space:
		break;
	case endln:
		A1b();
		break;
	case endf:
		Exit3();
		break;
	default:
		G1b();
	}
}

void Lex_an::D2()
{
	switch (RK)
	{
	case letter:
		q=&Lex_an::M3;
		break;
	case digit:
		D2a();
		break;
	case arifmetic_op:
		A2d();
		break;
	case relation:
		H1d();
		break;
	case l_br:
		A2m();
		break;
	case r_br:
		A3e();
		break;
	case space:
		break;
	case endln:
		A1c();
		break;
	case endf:
		Exit4();
		break;
	default:
		G1b();
	}
}

void Lex_an::D3()
{
	switch (RK)
	{
	case letter:
		D5a();
		break;
	case arifmetic_op:
		D4a();
		break;
	case space:
		break;
	default:
		G1b();
	}
}

void Lex_an::D4()
{
	switch (RK)
	{
	case letter:
		D5a();
		break;
	case arifmetic_op:
		A2a();
		break;
	case relation:
		H1a();
		break;
	case l_br:
		A2h();
		break;
	case r_br:
		A3b();
		break;
	case dot:
		q = &Lex_an::D6;
		break;
	case space:
		break;
	case endln:
		q = &Lex_an::A1;
		break;
	case endf:
		Exit1();
		break;
	default:
		G1b();
	}
}

void Lex_an::D5()
{
	switch (RK)
	{
	case letter:
		B1c();
		break;
	case digit:
		D5c();
		break;
	case arifmetic_op:
		A2e();
		break;
	case relation:
		H1c();
		break;
	case l_br:
		A2n();
		break;
	case r_br:
		A3f();
		break;
	case space:
		break;
	case endln:
		A1d();
		break;
	case endf:
		Exit5();
		break;
	default:
		G1b();
	}
}

void Lex_an::D6()
{
	switch (RK)
	{
	case digit:
		D2b();
		break;
	case space:
		break;
	default:
		G1b();
	}
}

void Lex_an::E1()
{
	switch (RK)
	{
	case digit:
		E2b();
		break;
	case space:
		break;
	default:
		G1b();
	}
}

void Lex_an::E2()
{
	switch (RK)
	{
	case letter:
		B1e();
		break;
	case digit:
		E2c();
		break;
	case arifmetic_op:
		A2f();
		break;
	case relation:
		H1f();
		break;
	case l_br:
		A2j();
		break;
	case r_br:
		A3g();
		break;
	case space:
		break;
	case endln:
		A1e();
		break;
	default:
		G1b();
	}
}

void Lex_an::F1()
{
	switch (RK)
	{
	case letter:
		F2a();
		break;
	case space:
		break;
	case endln:
		A1e();
		break;
	default:
		G1b();
	}
}

void Lex_an::F2()
{
	switch (RK)
	{
	case digit:
		F3a();
		break;
	case relation:
		A2o();
		break;
	case space:
		break;
	default:
		G1b();
	}
}

void Lex_an::F3()
{
	switch (RK)
	{
	case relation:
		A2o();
		break;
	case space:
		break;
	default:
		G1b();
	}
}

void Lex_an::G1()
{
	switch (RK)
	{
	case letter:
		break;
	case digit:
		break;
	case arifmetic_op:
		break;
	case relation:
		break;
	case l_br:
		break;
	case r_br:
		break;
	case dot:
		break;
	case space:
		break;
	case endln:
		q=&Lex_an::A1;
		break;
	case endf:
		Exit1();
		break;
	default:
		G1b();
	}
}

void Lex_an::H1()
{
	switch (RK)
	{
	case letter:
		C2b();
		break;
	case digit:
		D1c();
		break;
	case arifmetic_op:
		A2g();
		break;
	case relation:
		A2p();
		break;
	case l_br:
		A2k();
		break;
	case r_br:
		A3c();
		break;
	case dot:
		D6a();
		break;
	case space:
		break;
	case endln:
		A1a();
		break;
	case endf:
		Exit2();
		break;
	default:
		G1b();
	}
}

void Lex_an::M1()
{
	if (ROB == 0)
	{
		G1b();
		return;
	}
	if (RZN == table[ROB - 1].letter)
		this->(table[ROB - 1].q)();
	else
	{
		ROB = table[ROB - 1].alternative;
		if (ROB)
			this->(table[ROB - 1].q)();
		else
			G1b();
	}
}

void Lex_an::M2()
{
	if (RZN == 5)
	{
		D3a();
		return;
	}
	else
	{
		create_lexeme();
		ROB = init_vect[RZN - 1];
		q = &Lex_an::B1;
	}
}

void Lex_an::M3()
{
	if (RZN == 5)
		q = q = &Lex_an::D3;
}

void Lex_an::Exit1()
{
	RKL = ENDF;
	create_lexeme();
}

void Lex_an::Exit2()
{
	create_lexeme();
	RKL = ENDF;
	create_lexeme();
}

void Lex_an::Exit3()
{
	create_lexeme();
	RKL = ENDF;
	create_lexeme();
}

void Lex_an::Exit4()
{
	create_lexeme();
	RKL = ENDF;
	create_lexeme();
}

void Lex_an::Exit5()
{
	create_lexeme();
	RKL = ENDF;
	create_lexeme();
}

void error2()
{
	RKL = ERROR;
	create_lexeme();
	RKL = ENDF;
	create_lexeme();
}