#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <variant>
#include "locale.h"
#include <unordered_map>
#include <vector>
#include <iomanip>
#include "lexAnalayserConst.h"
#include "strTable.h"
using namespace std;
#pragma once
enum simbolicToken
{
	letter,
	digit,
	arifmetic_operator,
	rel,
	l_bracket,
	r_bracket,
	dot,
	space,
	EndLn,
	end,
	other
};
enum Lexeme_class
{
	ROWLABEL = 1,
	OPERAND,
	ATTIT,
	NEXT,
	LET,
	FOR,
	GOTO,
	GOSUB,
	L_BRACKET,
	R_BRACKET,
	IF,
	RETURN,
	END,
	_TO,
	STEP,
	REM,
	_ERROR,
	ENDFILE,
	AR_OP
};


class Lexical_analyzer
{
private:
	ofstream file_errors;
	string str;
	typedef void(Lexical_analyzer::* pfuncType)();	//указатель на функицю состояния
	pfuncType q;
	int RCH,		// регистр числа
		RZ,			// регистр знака
		RP,			// регистр порядка
		RS,			// регистр счетчика
		RKL,		// регистр класса лексем 
		ROT,		// регистрп значения отношения  
		RZN,		// регистр значения символа
		RSOS,		// регистр состояния 
		ROB,		// регистр обнаружения
		RK,			// регистр значения класса символа  
		RSTR,		// регистр строки 
		RI,			// регистр номера буквы в имени переменной 
		RSE;		// регистр счетчика ошибок

	vector <int> start_vector;

	void A1()
	{
		switch (RK)
		{
		case digit:
			E2a();
			break;
		case space:
			break;
		case EndLn:
			break;
		default:
			RSE++;
			G1b();
		}
	}
	void A2()
	{
		switch (RK)
		{
		case letter:
			C2a();
			break;
		case digit:
			D1a();
			break;
		case arifmetic_operator:
			A2a();
			break;
		case rel:
			H1a();
			break;
		case l_bracket:
			A2h();
			break;
		case r_bracket:
			A3b();
			break;
		case dot:
			D6b();
			break;
		case space:
			break;
		case EndLn:
			q = &Lexical_analyzer::A1;
			break;
		}
	}
	void A3()
	{
		switch (RK)
		{
		case letter:
			B1a();
			break;
		case digit:
			D1a();
			break;
		case arifmetic_operator:
			A2a();
			break;
		case rel:
			H1a();
			break;
		case l_bracket:
			A2h();
			break;
		case r_bracket:
			A3b();
			break;
		case dot:
			D6b();
			break;
		case space:
			break;
		case EndLn:
			q = &Lexical_analyzer::A1;
			break;
		}
	}
	void B1()
	{
		switch (RK)
		{
		case letter:
			M1();
			break;
		case space:
			break;
		case EndLn:
			A1f();
			break;
		default:
			RSE++;
			G1b();
		}
	}
	void C1()
	{
		switch (RK)
		{
		case letter:
			C2d();
			break;
		case space:
			break;
		default:
			G1b();
		}
	}
	void C2()
	{
		switch (RK)
		{
		case letter:
			B1b();
			break;
		case digit:
			A3a();
			break;
		case arifmetic_operator:
			A2g();
			break;
		case rel:
			H1b();
			break;
		case l_bracket:
			A2k();
			break;
		case r_bracket:
			A3c();
			break;
		case space:
			break;
		case EndLn:
			A1a();
			break;
		default:
			G1b();

		}
	}
	void D1()
	{
		switch (RK)
		{
		case letter:
			M2();
			break;
		case digit:
			D1b();
			break;
		case arifmetic_operator:
			A2c();
			break;
		case rel:
			H1c();
			break;
		case l_bracket:
			A2l();
			break;
		case r_bracket:
			A3d();
			break;
		case dot:
			D2c();
			break;
		case space:
			break;
		case EndLn:
			A1b();
			break;
		}
	}
	void D2()
	{
		switch (RK)
		{
		case letter:
			M3();
			break;
		case digit:
			D2a();
			break;
		case arifmetic_operator:
			A2c();
		case rel:
			H1c();
		case l_bracket:
			A2l();
		case r_bracket:
			A3d();
			break;
		case space:
			break;
		case EndLn:
			A1c();
			break;
		default:
			G1b();
		}
	}
	void D3()
	{
		switch (RK)
		{
		case digit:
			D5a();
			break;
		case arifmetic_operator:
			D4a();
			break;
		case space:
			break;
		default:
			G1b();
		}

	}
	void D4()
	{
		switch (RK)
		{
		case digit:
			D5b();
			break;
		case space:
			break;
		default:
			G1b();
		}
	}
	void D5()
	{
		switch (RK)
		{
		case letter:
			B1c();
			break;
		case digit:
			D5c();
			break;
		case rel:
			H1c();
			break;
		case l_bracket:
			A2l();
			break;
		case r_bracket:
			A3d();
			break;
		case space:
			break;
		case EndLn:
			A1d();
			break;
		default:
			G1b();
		}
	}
	void D6()
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
	void E1()
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
	void E2()
	{
		switch (RK)
		{
		case letter:
			B1e();
			break;
		case digit:
			E2c();
			break;
		case rel:
			H1f();
			break;
		case space:
			break;
		case arifmetic_operator:
			A2f();
			break;
		case l_bracket:
			A2j();
			break;
		case r_bracket:
			A3g();
		case EndLn:
			A1e();
			break;
		default:
			G1b();

		}
	}
	void F1()
	{
		switch (RK)
		{
		case letter:
			F2a();
			break;
		case space:
			break;
		default:
			G1b();

		}
	}
	void F2()
	{
		switch (RK)
		{
		case digit:
			F3a();
			break;
		case rel:
			A2o();
			break;
		case space:
			break;
		default:
			G1b();

		}
	}
	void F3()
	{
		switch (RK)
		{
		case rel:
			A2o();
			break;
		case space:
			break;
		default:
			RSE++;
			G1b();
		}
	}
	void G1()
	{
		switch (RK)
		{
		case EndLn:
			q = &Lexical_analyzer::A1;
			break;
		default:
			q = &Lexical_analyzer::G1;
		}
	}
	void H1()
	{
		switch (RK)
		{
		case letter:
			C2b();
			break;
		case digit:
			D1c();
			break;
		case arifmetic_operator:
			A2g();
			break;
		case rel:
			A2p();
			break;
		case l_bracket:
			A2k();
			break;
		case r_bracket:
			A3c();
			break;
		case dot:
			D6a();
			break;
		case space:
			break;
		case EndLn:
			A1a();
			break;
		}
	}
	void transliterator(char ch)
	{
		if (ch >= 'A' && ch <= 'Z')
		{
			RK = letter;
			RZN = ch - 'A';
		}
		if (ch >= '0' && ch <= '9')
		{
			RK = digit;
			RZN = ch - '0';
		}
		if (ch == '+')
		{
			RK = arifmetic_operator;
			RZN = 1;
		}
		if (ch == '-')
		{
			RK = arifmetic_operator;
			RZN = 2;
		}
		if (ch == '*')
		{
			RK = arifmetic_operator;
			RZN = 3;
		}
		if (ch == '/')
		{
			RK = arifmetic_operator;
			RZN = 4;
		}
		if (ch == '^')
		{
			RK = arifmetic_operator;
			RZN = 5;
		}
		if (ch == ' ' || ch == '\t')
		{
			RK = space;
		}
		if (ch == '.')
		{
			RK = dot;
		}
		if (ch == '\n')
		{
			RK = EndLn;
		}
		if (ch == '(')
		{
			RK = l_bracket;
		}
		if (ch == ')')
		{
			RK = r_bracket;
		}
		if (ch == '=')
		{
			RK = rel;
			RZN = 1;
		}
		if (ch == '<')
		{
			RK = rel;
			RZN = 2;
		}
		if (ch == '>')
		{
			RK = rel;
			RZN = 3;
		}
	}
	void Parse()
	{
		for (int i = 0; i < str.size(); ++i)
		{
			transliterator(str[i]);
			(this->*q)();
		}
	}
	void End()
	{
		if (q == &Lexical_analyzer::A1 || q == &Lexical_analyzer::A2 || q == &Lexical_analyzer::A3 || q == &Lexical_analyzer::G1)
		{
			q == &Lexical_analyzer::exit1;
		}
		else
			if (q == &Lexical_analyzer::C1 || q == &Lexical_analyzer::D1)
			{
				q == &Lexical_analyzer::exit3;
			}
			else
				if (q == &Lexical_analyzer::C2 || q == &Lexical_analyzer::D2)
				{
					q == &Lexical_analyzer::exit4;
				}
				else
					if (q == &Lexical_analyzer::H1)
					{
						q == &Lexical_analyzer::exit2;
					}
					else
						if (q == &Lexical_analyzer::D5)
						{
							q == &Lexical_analyzer::exit5;
						}
						else
							q == &Lexical_analyzer::error2;

		(this->*q)();
		SaveLex();
		SaveOper();
		SaveLabel();
		file_errors.close();
	}
	void CreateToken()
	{
		Lexeme t;
		t.LexemeClass = RKL;
		t.LexemeValue = -1;
		if (RKL == ROWLABEL || RKL == GOTO || RKL == GOSUB) {
			// Добавляем метку в хеш-таблицу TS
			int koef;
			if (RKL == ROWLABEL)
			{

				if (koef = TS.Find(RSTR) != -1)     // такая метка уже есть => проверить, была ли она почле GOTO\GOSUB или встречалась ранее
				{
					if (TS.TLinf(koef) == -1)		// => была после GOTO\GOSUB и еще не встречалась
					{
						TS.el_del(RSTR);
						TS.el_add(RSTR, NTL);
						t.LexemeValue = TS.Find(RSTR);

					}
					else
						cerr << "повторное вхождение метки\n";
				}
			}
			else // идет после GOTO\GOSUB и строки с такой метки может еще не быть
			{
				if (koef = TS.Find(RSTR) != -1) // => така уже есть где то
				{
					t.LexemeValue = koef;
				}
				else  // такой ещё нет => добавить но с -1 в связи с ТЛ
				{
					koef = TS.el_add(RSTR, -1);
					t.LexemeValue = koef;
				}
			}
			RSTR = 0; // Сброс регистра строки
		}

		if (RKL == OPERAND || RKL == NEXT) {
			if (RI != 0) { // Идентификатор
				int n = (RK == digit) ? (RI + 26 * (RZN + 1)) : RI;
				TO[n] = 1;
				t.LexemeValue = n;
				RI = 0;
			}
			else { // Константа
				double value = RCH * pow(10, RZ * (RP - RS)); // Вычисление значения
				// Поиск существующей константы в TO
				bool found = false;
				for (int i = 287; i < NTO; ++i) {
					if (TO[i] == value) {
						t.LexemeValue = i;
						found = true;
						break;
					}
				}
				if (!found) {
					TO[NTO] = value;
					t.LexemeValue = NTO;
					NTO++;
				}
				// Сброс регистров
				RCH = RP = RS = 0;
				RZ = 1;
			}
		}
		if (RKL == LET || RKL == FOR)
		{
			TO[RI] = 1;
			t.LexemeValue = RI;
			RI = 0;
		}
		if (RKL == AR_OP)
		{
			t.LexemeValue = RZN;
		}
		if (RKL == ATTIT)
			t.LexemeValue = ROT;
		TL[NTL] = t;
		NTL++;
	}
	void SaveLex()
	{
		cout << "Таблица лексем:" << endl;
		cout << left << setw(5) << "№" << setw(15) << "Тип лексемы" << setw(10) << "Значение" << endl;
		cout << "--------------------------------------------------------" << endl;

		ofstream fout("result_lex.txt");
		if (!fout)
		{
			throw 1;
		}
		char Tclass[19][15] = { "LABEL", "OPERAND", "ATTITUDE", "NEXT", "LET", "FOR", "GOTO", "GOSUB", "LEFTBRACKET", "RIGHTBRACKET",
								 "IF", "RETURN", "END", "TO", "STEP", "REM", "ERROR", "ENDMARCER", "OPERATION" };

		for (int i = 1; i < NTL; i++)
		{
			fout.width(3);
			fout << i - 1 << "   " << Tclass[TL[i].LexemeClass - 1] << "  " << TL[i].LexemeValue << endl;

			// Выводим в консоль с выравниванием
			cout << left << setw(5) << i - 1
				<< setw(15) << Tclass[TL[i].LexemeClass - 1]
				<< setw(10) << TL[i].LexemeValue << endl;
		}
		fout.close();
	}

	void SaveOper()
	{
		cout << endl;
		cout << "Таблица операндов:" << endl;
		cout << left << setw(5) << "№" << setw(15) << "Операнд" << endl;
		cout << "--------------------------------------" << endl;

		ofstream fout("result_oper.txt");
		if (!fout)
		{
			throw 1;
		}

		for (int i = 1; i < 287; ++i)
		{
			fout.width(3);
			if (TO[i])
			{
				fout << i << " " << TO[i] << endl;

				// Выводим в консоль с выравниванием
				cout << left << setw(5) << i
					<< setw(15) << TO[i] << endl;
			}
		}

		for (int i = 287; i < NTO; ++i)
		{
			fout.width(3);
			fout << i << " " << TO[i] << endl;

			// Выводим в консоль с выравниванием
			cout << left << setw(5) << i
				<< setw(15) << TO[i] << endl;
		}
		fout.close();
	}

	void SaveLabel() {
		cout << "Таблица меток:" << endl;
		ofstream fout("result_label.txt");
		TS.print(fout);
	}

	struct node
	{
		int letter;
		int alternative;
		void(Lexical_analyzer::* pfunc)();
	};

	// Функция для инициализации таблицы обнаружения
	void InitializeStartVector() {
		start_vector.resize(26);
		for (int i = 0; i < start_vector.size(); i++)
			start_vector[i] = -1;
		start_vector['E' - 'A'] = 0;    // END
		start_vector['F' - 'A'] = 2;    // FOR
		start_vector['G' - 'A'] = 4;    // GOTO, GOSUB
		start_vector['I' - 'A'] = 10;   // IF
		start_vector['L' - 'A'] = 11;   // LET
		start_vector['N' - 'A'] = 13;   // NEXT
		start_vector['R' - 'A'] = 16;   // RETURN, REM
		start_vector['S' - 'A'] = 22;   // STEP
		start_vector['T' - 'A'] = 25;   // TO
	}

	// Функция для инициализации таблицы альтернатив
	void InitializeTable() {
		
		for (int i = 0; i < 26; ++i) {
			table[i].alternative = -1;					// Нет альтернатив по умолчанию
			table[i].pfunc = &Lexical_analyzer::next;   // По умолчанию функция "next"
		}

		table[0].letter = 'N' - 'A';
		table[1].letter = 'D' - 'A';
		table[1].pfunc = &Lexical_analyzer::A2q; // Функция для END 
		table[2].letter = 'O' - 'A';
		table[3].letter = 'R' - 'A';
		table[3].pfunc = &Lexical_analyzer::F1b; // Функция для FOR 
		table[4].letter = 'O' - 'A';
		table[4].alternative = 7;		   // альтернатива - GOSUB
		table[5].letter = 'T' - 'A';
		table[6].letter = 'O' - 'A';
		table[6].pfunc = &Lexical_analyzer::E1a; //функция для GOTO
		table[7].letter = 'S' - 'A';
		table[8].letter = 'U' - 'A';
		table[9].letter = 'B' - 'A';
		table[9].pfunc = &Lexical_analyzer::E1b; // функция для GOSUB
		table[10].letter = 'F' - 'A';
		table[10].pfunc = &Lexical_analyzer::A2r; // Функция для IF 
		table[11].letter = 'E' - 'A';
		table[12].letter = 'T' - 'A';
		table[12].pfunc = &Lexical_analyzer::F1a; // Функция для LET
		table[13].letter = 'E' - 'A';
		table[14].letter = 'X' - 'A';
		table[15].letter = 'T' - 'A';
		table[15].pfunc = &Lexical_analyzer::C1a; // Функция для NEXT
		table[16].letter = 'E' - 'A';
		table[17].letter = 'T' - 'A';
		table[17].alternative = 21;
		table[18].letter = 'U' - 'A';
		table[19].letter = 'R' - 'A';
		table[20].letter = 'N' - 'A';
		table[20].pfunc = &Lexical_analyzer::A2s; // Функция для RETURN
		table[21].letter = 'M' - 'A';
		table[21].pfunc = &Lexical_analyzer::G1a; // Функция для REM
		table[22].letter = 'T' - 'A';
		table[23].letter = 'E' - 'A';
		table[24].letter = 'P' - 'A';
		table[24].pfunc = &Lexical_analyzer::A2t; // Функция для STEP
		table[25].letter = 'O' - 'A';
		table[25].pfunc = &Lexical_analyzer::A2u; // Функция для TO
	}


public:
	Lexical_analyzer() :
		start_vector(26, 0),
		table(26),
		TL(512),
		TS(512),
		file_errors("errors.txt"),
		NTO(287),
		NTL(1),
		NTS(1),
		RZ(1),
		RI(0),
		RCH(0),
		RP(0),
		RS(0),
		RSE(0)
	{
		memset(TO, 0, sizeof(TO));	// инициализирует таблицу операндов нулями

		InitializeStartVector();	

		InitializeTable();

		q = &Lexical_analyzer::A1;
	}

	void start(const char* filename)
	{
		ifstream fin(filename);
		if (!fin)
		{
			throw 1;
		}
		while (!fin.eof())
		{
			getline(fin, str);
			str += '\n';
			Parse();
			str.clear();
		}
		End();
		fin.close();
	}
	struct Lexeme
	{
		int LexemeClass;
		int LexemeValue;
	};
	Hash TS;				//таблица строк
	vector <Lexeme> TL;		//таблица лексем
	double TO[1024];		//таблица операндов 
	int NTO;				// указатель на первый свободный элемент в TO
	int NTS;				// указатель на первый свободный элемент в TS
	int NTL;				// указатель на первый свободный элемент в TL

	vector<node> table;		//таблица альтернатив

	void next()
	{
		ROB++;
	}
	void A1a()
	{
		CreateToken();
		q = &Lexical_analyzer::A1;
	}
	void A1b()
	{
		RP = 0;
		CreateToken();
		q = &Lexical_analyzer::A1;
	}
	void A1c()
	{
		CreateToken();
		q = &Lexical_analyzer::A1;
	}
	void A1d()
	{
		CreateToken();
		q = &Lexical_analyzer::A1;
	}
	void A1e()
	{
		A1a();
		q = &Lexical_analyzer::A1;
	}
	void A1f()
	{
		RKL = _ERROR;
		CreateToken();
		q = &Lexical_analyzer::A1;
	}
	void A2a()
	{
		RKL = AR_OP;
		CreateToken();
		q = &Lexical_analyzer::A2;
	}
	void A2b()
	{
		CreateToken();
		q = &Lexical_analyzer::A2;
	}
	void A2c()
	{
		CreateToken();
		RKL = AR_OP;
		CreateToken();
		q = &Lexical_analyzer::A2;
	}
	void A2h()
	{
		RKL = L_BRACKET;
		CreateToken();
		q = &Lexical_analyzer::A2;
	}
	void A2l()
	{
		CreateToken();
		RKL = L_BRACKET;
		CreateToken();
		q = &Lexical_analyzer::A2;
	}
	void A2g()
	{
		CreateToken();
		RKL = AR_OP;
		CreateToken();
		q = &Lexical_analyzer::A2;
	}
	void A2p()
	{
		if (ROT == 2 && RZN == 1)
		{
			ROT = 4;
		}
		else
			if (ROT == 3 && RZN == 1)
				ROT = 5;
			else
				if (ROT == 2 && RZN == 3)
					ROT = 6;
		CreateToken();
		q = &Lexical_analyzer::A2;
	}
	void A2r()
	{
		RKL = IF;
		A2b();
		q = &Lexical_analyzer::A2;
	}
	void A2k()
	{
		CreateToken();
		RKL = L_BRACKET;
		CreateToken();
		q = &Lexical_analyzer::A2;
	}
	void A2s()
	{
		RKL = RETURN;
		A2b();
		q = &Lexical_analyzer::A2;
	}
	void A2q()
	{
		RKL = END;
		A2b();
		q = &Lexical_analyzer::A2;
	}
	void A2o()
	{
		if (RZN == 1)
		{
			CreateToken();
		}
		else
		{
			G1b();
			return;
		}
		q = &Lexical_analyzer::A2;
	}
	void A2u()
	{
		RKL = _TO;
		A2b();
		q = &Lexical_analyzer::A2;
	}
	void A2j()
	{
		CreateToken();
		RKL = L_BRACKET;
		CreateToken();
		q = &Lexical_analyzer::A2;
	}
	void A2f()
	{
		CreateToken();
		RKL = AR_OP;
		CreateToken();
		q = &Lexical_analyzer::A2;
	}
	void A2t()
	{
		RKL = STEP;
		A2b();
		q = &Lexical_analyzer::A2;
	}
	void A3a()
	{
		CreateToken();
		q = &Lexical_analyzer::A3;
	}
	void A3b()
	{
		RKL = R_BRACKET;
		CreateToken();
		q = &Lexical_analyzer::A3;
	}
	void A3c()
	{
		CreateToken();
		RKL = R_BRACKET;
		CreateToken();
		q = &Lexical_analyzer::A3;
	}
	void A3d()
	{
		CreateToken();
		RKL = R_BRACKET;
		CreateToken();
		q = &Lexical_analyzer::A3;
	}
	void A3g()
	{
		CreateToken();
		RKL = R_BRACKET;
		CreateToken();
		q = &Lexical_analyzer::A3;
	}
	void B1a()
	{
		ROB = start_vector[RZN];
		q = &Lexical_analyzer::B1;
	}
	void B1b()
	{
		CreateToken();
		ROB = start_vector[RZN];
		q = &Lexical_analyzer::B1;
	}
	void B1c()
	{
		CreateToken();
		ROB = start_vector[RZN];
		q = &Lexical_analyzer::B1;
	}
	void B1e()
	{
		CreateToken();
		ROB = start_vector[RZN];
		q = &Lexical_analyzer::B1;
	}
	void C1a()
	{
		RKL = NEXT;
		q = &Lexical_analyzer::C1;
	}
	void C2a()
	{
		RKL = OPERAND;
		RI = RZN;
		q = &Lexical_analyzer::C2;
	}
	void C2b()
	{
		CreateToken();
		RKL = OPERAND;
		RI = RZN;
		q = &Lexical_analyzer::C2;
	}
	void C2d()
	{
		RI = RZN;
		q = &Lexical_analyzer::C2;
	}
	void D1a()
	{
		RKL = OPERAND;
		RCH = RZN;
		q = &Lexical_analyzer::D1;
	}
	void D1b()
	{
		RCH *= 10;
		RCH += RZN;
		q = &Lexical_analyzer::D1;
	}
	void D1c()
	{
		CreateToken();
		RKL = OPERAND;
		RCH = RZN;
		q = &Lexical_analyzer::D1;
	}
	void D2a()
	{
		RS++;
		RCH *= 10;
		RCH += RZN;
		q = &Lexical_analyzer::D2;
	}
	void D2b()
	{
		RS = 1;
		RCH = RZN;
		q = &Lexical_analyzer::D2;
	}
	void D2c()
	{
		RS = 0;
		q = &Lexical_analyzer::D2;
	}
	void D3a()
	{
		RS = 0;
		q = &Lexical_analyzer::D3;
	}
	void D4a()
	{
		if (RZN == 1)
		{
			RZ = 1;
		}
		else
			if (RZN == 2)
				RZ = -1;
		q = &Lexical_analyzer::D4;
	}
	void D5a()
	{
		RZ = 1;
		RP = RZN;
		q = &Lexical_analyzer::D5;
	}
	void D5b()
	{
		RP = RZN;
		q = &Lexical_analyzer::D5;
	}
	void D5c()
	{
		RP *= 10;
		RP += RZN;
		q = &Lexical_analyzer::D5;
	}
	void D6a()
	{
		CreateToken();
		RKL = OPERAND;
		q = &Lexical_analyzer::D6;
	}
	void D6b()
	{
		RKL = OPERAND;
		q = &Lexical_analyzer::D6;
	}
	void E1a()
	{
		RKL = GOTO;
		q = &Lexical_analyzer::E1;
	}
	void E1b()
	{
		RKL = GOSUB;
		q = &Lexical_analyzer::E1;
	}
	void E2a()
	{
		RKL = ROWLABEL;
		RSTR = RZN;
		q = &Lexical_analyzer::E2;
	}
	void E2b()
	{
		RSTR = RZN;
		q = &Lexical_analyzer::E2;
	}
	void E2c()
	{
		RSTR *= 10;
		RSTR += RZN;
		q = &Lexical_analyzer::E2;
	}
	void F1a()
	{
		RKL = LET;
		q = &Lexical_analyzer::F1;
	}
	void F1b()
	{
		RKL = FOR;
		q = &Lexical_analyzer::F1;
	}
	void F2a()
	{
		RI = RZN;
		q = &Lexical_analyzer::F2;
	}
	void F3a()
	{
		RI += (RZN) * 26;
		q = &Lexical_analyzer::F3;
	}
	void G1a()
	{
		RKL = REM;
		CreateToken();
		q = &Lexical_analyzer::G1;
	}
	void G1b()
	{
		RKL = _ERROR;
		CreateToken();
		q = &Lexical_analyzer::G1;
	}
	void H1a()
	{
		RKL = ATTIT;
		ROT = RZN;
		q = &Lexical_analyzer::H1;
	}
	void H1b()
	{
		CreateToken();
		RKL = ATTIT;
		ROT = RZN;
		q = &Lexical_analyzer::H1;
	}
	void H1c()
	{
		CreateToken();
		RKL = ATTIT;
		ROT = RZN;
		q = &Lexical_analyzer::H1;
	}
	void H1f()
	{
		H1b();
		RKL = ATTIT;
		ROT = RZN;
		q = &Lexical_analyzer::H1;
	}
	void M1()
	{
		if (ROB == -1)
		{
			G1b();
			return;
		}
		if (RZN == table[ROB].letter)
		{
			(this->*(table[ROB].pfunc))();
		}
		else
		{
			ROB = table[ROB].alternative;
			if (ROB != -1)
			{
				(this->*(table[ROB].pfunc))();
			}
			else
				G1b();
		}
	}
	void M2()
	{
		if (RZN == 4)
		{
			D3a();
			return;
		}
		else
		{
			CreateToken();
			ROB = start_vector[RZN];
			q = &Lexical_analyzer::B1;
		}
	}
	void M3()
	{
		if (RZN == 4)
		{
			q = &Lexical_analyzer::D3;
		}
	}
	void exit1()
	{
		RKL = ENDFILE;
		CreateToken();
	}
	void exit2()
	{
		CreateToken();
		RKL = ENDFILE;
		CreateToken();
	}
	void exit3()
	{
		CreateToken();
		RKL = ENDFILE;
		CreateToken();
	}
	void exit4()
	{
		CreateToken();
		RKL = ENDFILE;
		CreateToken();
	}
	void exit5()
	{
		CreateToken();
		RKL = ENDFILE;
		CreateToken();
	}
	void error2()
	{
		RKL = _ERROR;
		CreateToken();
		RKL = ENDFILE;
		CreateToken();
	}

};
int main()
{
	setlocale(LC_ALL, "RUS");
	try {
		Lexical_analyzer analyzer;
		analyzer.start("test.txt"); // Укажите имя вашего файла с кодом
		cout << "Лексический анализ успешно завершен!\n";
		cout << "Результаты сохранены в файлах:\n"
			<< " - result_lex.txt (лексемы)\n"
			<< " - result_oper.txt (операнды)\n"
			<< " - result_label.txt (метки)\n";
	}
	catch (...) {
		cerr << "Ошибка при выполнении анализа!\n"
			<< "Проверьте входноq файл\n";
		return 1;
	}
	return 0;
}