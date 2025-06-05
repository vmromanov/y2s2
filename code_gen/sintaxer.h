#pragma once
#include <stack>
#include "lexer.h"
#include "Atoms.h"
using namespace std;
class Syntax_analyzer : public Lex_Analyzator
{
public:

    void PrintTA() {
        cout << "ТАБЛИЦА АТОМОВ" << endl;
        cout << string(60, '-') << endl;

        // Заголовок таблицы
        cout << setw(25) << left << "Тип";
        cout << setw(10) << left << "Attr1";
        cout << setw(10) << left << "Attr2";
        cout << setw(10) << left << "Attr3";
        cout << setw(10) << left << "Attr4";
        cout << endl << string(60, '-') << endl;

        // Вывод данных
        for (const auto& atom : table_atoms)
        {
            cout << setw(25) << left << AtomTypeString[atom.type];
            cout << setw(10) << left << (atom.attribute1 != -1 ? to_string(atom.attribute1) : "-");
            cout << setw(10) << left << (atom.attribute2 != -1 ? to_string(atom.attribute2) : "-");
            cout << setw(10) << left << (atom.attribute3 != -1 ? to_string(atom.attribute3) : "-");
            cout << setw(10) << left << (atom.attribute4 != -1 ? to_string(atom.attribute4) : "-");
            cout << endl;
        }
        cout << string(60, '-') << endl;
    }
    void PrintStk() {
        cout << "Stk" << endl;
        stack<int> temp;
        for (int i = 0; i < stk.size();)
        {
            cout << stk.top() << " " << endl;
            temp.push(stk.top());
            stk.pop();
        }
        for (int i = 0; i < temp.size();)
        {
            stk.push(temp.top());
            temp.pop();
        }
        cout << endl;
    }

   Syntax_analyzer():ferr("errors.txt"),
       in(1),
       NTX(1),
       NTM(1),
       flagErr(0) 
   {
       Create_Control_Table();

       stk.push(18);
       stk.push(1);
   }

   void start(const char* name_file) override {
       
       Lex_Analyzator::start(name_file);

       if (RSE)
       {
           Error("Ошибки при лексическом анализе\n");
           return;
       }

       NTtemp = NTO;
       NTX = 700;
       NTM = 256;

       for (int i = 1; i < TL.size(); i++)
       {
           switch (TL[i].TokenClass)
           {
           case 17:
               TL[i].TokenClass = 22;
               break;
           case 18:
               TL[i].TokenClass = 23;
               break;
           case 19:
               TL[i].TokenClass = TL[i].TokenClass = 16 + TL[i].TokenValue;
               break;
           }
       }
       int temp_par = -1;
       int sz=0;
       for (int i = 1; i < TL.size(); i++)
       {
           if (TL[i].TokenClass == 0)
           {
               sz = i;
               break;
           }
       }
       while (in < sz )
       {
           temp_par = stk.top();
           if (test_flag)
           {
               cout << temp_par << " " << TL[in].TokenClass << endl;
               PrintStk();
               PrintTA();
               cout << endl;
           }
           (this->*Control_Table[temp_par][TL[in].TokenClass])();
       }

       if (flagErr)
       {
           cout << "Errors are present" << endl;
       }

       PrintStk();
       PrintTA();
       cout << endl;

       ferr.close();
   }

   bool test_flag = 0;

protected:
    ofstream ferr;
   vector<Atom> table_atoms;

   typedef void(Syntax_analyzer::* func) ();
   func Control_Table[34][24];

   stack <int> stk;
   int in;              //Указатель на индекс входной лексемы
   int num_str;         //Номер текущей строки
   vector<int> TM;      //Таблица меток
   int NTM;             //Указатель на первый свободный элемент таблицы меток

   vector<int> TX;      //Таблица для хранения результатов атома хранения
   int NTX;             //Указатель на первый свободный элемент таблицы результатов атома хранения
   bool flagErr;        //Вид обнаружения ошибки
   int NTtemp;          //Указатель на первый свободный элемент в таблицы промежуточных результатов

   void Create_Atom(int type, int a = -1, int b = -1, int c = -1, int d = -1) {
       Atom A;
       
       A.type = type;
       A.attribute1 = a;
       A.attribute2 = b;
       A.attribute3 = c;
       A.attribute4 = d;
       table_atoms.push_back(A);
   }

   void Error(string errMsg) {
       
       ferr << "Oшибка: Cтpoka " << num_str << ' ' << errMsg << endl;
       flagErr = true;

       if (TL[in].TokenClass == 23)
       {
           in++;
       }
       else
       {
           while (in < TL.size() && TL[in].TokenClass != 1)
               in++;
       }

       if (stk.top() == 1 || stk.top() == 2 || stk.top() == 4)
           return;
       else if (stk.top() == 16 || stk.top() == 18)
       {
           stk.pop(); stk.push(2);
       }
       else
       {
           while (stk.top() != 4)
               stk.pop();
       }
   }
   
   void F1()
   {
       stk.pop();
       stk.push(16);
       stk.push(2);
       cout << TL[in].TokenClass << ' ' << TL[in].TokenValue << endl;
       Create_Atom(1, TL[in].TokenValue);

       num_str = TS.TL_L_inf(TL[in].TokenValue);
       in++;

   }
   void F2()
   {
       stk.pop();
       int k = stk.top();
   }
   void F3()
   {
       Create_Atom(1, TL[in].TokenValue);
       num_str = TS.TL_L_inf(TL[in].TokenValue);
       in++;
   }
   void F4()
   {
       stk.pop();
       stk.push(4);//другие строки
       stk.push(0);
       stk.push(TL[in].TokenValue);
       stk.push(19);//присв
       stk.push(3);
       stk.push(5);//выражение
       in++;
   }
   void F5()
   {
       stk.pop();
       stk.push(4);
       Create_Atom(3, TL[in].TokenValue);
       in++;
   }
   void F6()
   {
       stk.pop();
       stk.push(4);
       stk.push(0);
       stk.push(0);
       stk.push(0);
       stk.push(0);
       stk.push(20);
       stk.push(5);
       stk.push(14);
       stk.push(5);
       stk.push(5);
       stk.push(8);
       stk.push(12);
       stk.push(8);
       stk.push(5);
       in++;
   }
   void F7()
   {
       stk.pop();
       stk.push(4);
       Create_Atom(4, TL[in].TokenValue);
       in++;
   }
   void F8()
   {
       stk.pop();
       stk.push(4);
       Create_Atom(5);
       in++;
   }
   void F9()
   {
       int p, s, t, u, v, y;
       p = TL[in].TokenValue;// Значение входа
       s = NTX;// Значение поставляемому вызовом процедуры НОВТX
       NTX++;
       t = NTX;// Значение поставляемому другим вызовом процедуры НОВТХ
       NTX++;
       u = NTM;// значение поставляемому вызовом процедуры НОВТАМ
       NTM++;
       v = NTM;//значение поставляемому другим вызовом процедуры НОВТАМ
       NTM++;
       y = num_str;
       stk.pop();
       stk.push(4);
       stk.push(v);
       stk.push(22);
       stk.push(u);
       stk.push(26);
       stk.push(t);
       stk.push(p);
       stk.push(25);
       stk.push(y);
       stk.push(0);
       stk.push(p);
       stk.push(24);
       stk.push(3);
       stk.push(13);
       stk.push(4);
       stk.push(v);
       stk.push(t);
       stk.push(s);
       stk.push(p);
       stk.push(23);
       stk.push(u);
       stk.push(22);
       stk.push(t);
       stk.push(0);
       stk.push(21);
       stk.push(2);
       stk.push(3);
       stk.push(s);
       stk.push(0);
       stk.push(21);
       stk.push(2);
       stk.push(5);
       stk.push(17);
       stk.push(0);
       stk.push(p);
       stk.push(19);
       stk.push(3);
       stk.push(5);
       in++;
   }
   void F10()
   {
       stk.pop();
       stk.push(5);
       in++;
   }
   void F11()
   {
       TO[NTO]=1;
       stk.pop();
       stk.pop();
       int p = stk.top();
       stk.pop();
       stk.pop();
       stk.push(TO[NTO]);
       stk.push(p);

       NTO++;
   }
   void F12()
   {
       stk.pop();
       stk.push(4);
       in++;
   }

   void F13()
   {
       stk.pop();
       stk.push(2);
       Create_Atom(1, TL[in].TokenValue);
       num_str = TS.TL_L_inf(TL[in].TokenValue);
       in++;
   }
   void F14()
   {
       stk.pop();
       stk.push(0);
       stk.push(9);
       stk.push(2);
       stk.push(6);
   }
   void F15()
   {
       stk.pop();
       stk.push(NTtemp);
       stk.push(9);
       stk.push(NTtemp);
       stk.push(0);
       stk.push(32);
       stk.push(2);
       stk.push(6);
       NTtemp++;
       in++;
   }

   void F16()
   {
       stk.pop();
       stk.push(NTtemp);
       stk.push(9);
       stk.push(NTtemp);
       stk.push(0);
       stk.push(33);
       stk.push(2);
       stk.push(6);
       NTtemp++;
       in++;
   }
   void F17()
   {
       stk.pop();
       int p = stk.top();
       stk.pop();
       stk.push(NTtemp);
       stk.push(9);
       stk.push(NTtemp);
       stk.push(0);
       stk.push(p);
       stk.push(27);
       stk.push(3);
       stk.push(6);
       NTtemp++;
       in++;
   }

   void F18()
   {
       stk.pop();
       int p = stk.top();
       stk.pop();
       stk.push(NTtemp);
       stk.push(9);
       stk.push(NTtemp);
       stk.push(0);
       stk.push(p);
       stk.push(28);
       stk.push(3);
       stk.push(6);
       NTtemp++;
       in++;
   }

   void F19()
   {
       stk.pop();
       int p = stk.top();
       stk.pop();
       int i = stk.top() - 1;
       stk.pop();
       stack<int> tmp;
       while (i > 0)
       {
           tmp.push(stk.top());
           stk.pop();
           i--;
       }

       while (stk.top() != 0)
       {
           tmp.push(stk.top());
           stk.pop();
       }
       stk.pop();
       stk.push(p);
       while (!tmp.empty())
       {
           stk.push(tmp.top());
           tmp.pop();
       }
   }


   void F20()
   {
       stk.pop();
       stk.push(0);
       stk.push(10);
       stk.push(2);
       stk.push(7);
   }
   void F21()
   {
       stk.pop();
       int p = stk.top();
       stk.pop();
       stk.push(NTtemp);
       stk.push(10);
       stk.push(NTtemp);
       stk.push(0);
       stk.push(p);
       stk.push(29);
       stk.push(3);
       stk.push(7);
       NTtemp++;
       in++;
   }


   void F22()
   {
       stk.pop();
       int p = stk.top();
       stk.pop();
       stk.push(NTtemp);
       stk.push(10);
       stk.push(NTtemp);
       stk.push(0);
       stk.push(p);
       stk.push(30);
       stk.push(3);
       stk.push(7);
       NTtemp++;
       in++;
   }

   void F23()
   {
       stk.pop();
       int p = stk.top();
       stk.pop();
       int i = stk.top() - 1;
       stk.pop();
       stack<int> tmp;
       while (i != 0)
       {
           tmp.push(stk.top());
           stk.pop();
           i--;
       }
       while (stk.top() != 0)
       {
           tmp.push(stk.top());
           stk.pop();
       }
       stk.pop();
       stk.push(p);
       while (!tmp.empty())
       {
           stk.push(tmp.top());
           tmp.pop();
       }
   }

   void F24()
   {
       stk.pop();
       stk.push(0);
       stk.push(11);
       stk.push(2);
       stk.push(8);
   }

   void F25()
   {
       stk.pop();
       int p = stk.top();
       stk.pop();
       int t = stk.top();
       stk.push(NTtemp);
       stk.push(11);
       stk.push(NTtemp);
       stk.push(0);
       stk.push(p);
       stk.push(31);
       stk.push(3);
       stk.push(8);
       NTtemp++;
       in++;
   }

   void F26()
   {
       stk.pop();
       int p = stk.top();
       stk.pop();
       int i = stk.top() - 1;
       stk.pop();
       stack<int> tmp;
       while (i > 0)
       {
           tmp.push(stk.top());
           stk.pop();
           i--;
       }

       while (stk.top() != 0)
       {
           tmp.push(stk.top());
           stk.pop();
       }
       stk.pop();
       stk.push(p);
       while (!tmp.empty())
       {
           stk.push(tmp.top());
           tmp.pop();
       }
   }

   void F27()
   {
       stk.pop();
       int p = stk.top();
       stk.pop();
       stk.push(15);
       stk.push(p);
       stk.push(5);
       in++;
   }

   void F28()
   {
       stk.pop();
       int i = stk.top() - 1;
       stk.pop();
       stack<int> tmp;
       while (i > 0)
       {
           tmp.push(stk.top());
           stk.pop();
           i--;
       }
       while (stk.top() != 0) 
       {
           tmp.push(stk.top());
           stk.pop();
       }
       stk.pop();
       stk.push(TL[in].TokenValue);
       while (!tmp.empty())
       {
           stk.push(tmp.top());
           tmp.pop();
       }
       in++;
   }

   void a() {
       stk.pop();
       in++;
   }
   void b() {
       stk.pop();
       int i = stk.top() - 1;
       stk.pop();
       stack<int> tmp;
       while (i != 0)
       {
           tmp.push(stk.top());
           stk.pop();
           i--;
       }
       stk.pop();
       stk.push(TL[in].TokenValue);
       while (!tmp.empty())
       {
           stk.push(tmp.top());
           tmp.pop();
       }
       in++;
   }
   void c() {
       Create_Atom(0);
       in++;
   }
   void d() {
       int k1, k2;
       stk.pop();
       k1 = stk.top();
       stk.pop();
       k2 = stk.top();
       stk.pop();
       Create_Atom(2, k1, k2);
   }
   void e() {
       int p, q, r, s;
       stk.pop();
       p = stk.top();
       stk.pop();
       q = stk.top();
       stk.pop();
       r = stk.top();
       stk.pop();
       s = stk.top();
       stk.pop();
       Create_Atom(6, p, q, r, s);
   }
   void f() {
       int p, q;
       stk.pop();
       p = stk.top();
       stk.pop();
       q = stk.top();
       stk.pop();
       Create_Atom(7, p, q);
   }
   void g() {
       int p;
       stk.pop();
       p = stk.top();
       stk.pop();
       Create_Atom(8, p);
   }
   void h() {
       int p, q, r, s;
       stk.pop();
       p = stk.top();
       stk.pop();
       q = stk.top();
       stk.pop();
       r = stk.top();
       stk.pop();
       s = stk.top();
       stk.pop();
       Create_Atom(9, p, q, r, s);
   }
   void i() {
       int k1, k2;
       stk.pop();
       k1 = stk.top();
       stk.pop();
       k2 = stk.top();
       stk.pop();
       if (k1 != k2)
       {
           Error("The variable in the 'next' statement is different from the variable in the 'for' statement");
       }
       stk.pop();
   }
   void j() {
       int p, q;
       stk.pop();
       p = stk.top();
       stk.pop();
       q = stk.top();
       stk.pop();
       Create_Atom(10, p, q);
   }
   void k() {
       int p;
       stk.pop();
       p = stk.top();
       stk.pop();
       Create_Atom(3, p);
   }
   void l() {
       int p, q, r;
       stk.pop();
       p = stk.top();
       stk.pop();
       q = stk.top();
       stk.pop();
       r = stk.top();
       stk.pop();
       Create_Atom(11, p, q, r);
   }
   void m() {
       int p, q, r;
       stk.pop();
       p = stk.top();
       stk.pop();
       q = stk.top();
       stk.pop();
       r = stk.top();
       stk.pop();
       Create_Atom(12, p, q, r);
   }
   void n() {
       int p, q, r;
       stk.pop();
       p = stk.top();
       stk.pop();
       q = stk.top();
       stk.pop();
       r = stk.top();
       stk.pop();
       Create_Atom(13, p, q, r);
   }
   void o() {
       int p, q, r;
       stk.pop();
       p = stk.top();
       stk.pop();
       q = stk.top();
       stk.pop();
       r = stk.top();
       stk.pop();
       Create_Atom(14, p, q, r);
   }
   void p() {
       int p, q, r;
       stk.pop();
       p = stk.top();
       stk.pop();
       q = stk.top();
       stk.pop();
       r = stk.top();
       stk.pop();
       Create_Atom(15, p, q, r);
   }
   void q() {
       int k1, k2;
       stk.pop();
       k1 = stk.top();
       stk.pop();
       k2 = stk.top();
       stk.pop();
       Create_Atom(16, k1, k2);
   }
   void r() {
       int k1, k2;
       stk.pop();
       k1 = stk.top();
       stk.pop();
       k2 = stk.top();
       stk.pop();
       Create_Atom(17, k1, k2);
   }

   void A() {
       Error("Программа начинается неверно.");
   }

   void B() {
       Error("Оператор начинается неверно.");
   }

   void G1() {
       Error("Неожиданный вход после for-оператора.");
   }
   void G2() {
       Error("Лишняя правая скобка в выражении после table_operands.");
   }

   void C() {
       Error(" ");
   }

   void D() {
       Error("Неожиданный вход после оператора.");
   }

   void K1() {
       Error("Выражение незаконно - нет операнда.");
   }
   void K2() {
       Error("Оператор незакончен.");
   }
   void K3() {
       Error("В выражении пропущен операнд.");
   }
   void K4() {
       Error("Неожиданный вход после выражения.");
   }
   void K5() {
       Error("Выражение начинается с недопустимого символа.");
   }
   void K6() {
       Error("Два знака операции в выражении.");
   }
   void K7() {
       Error("В выражении пропущен знак операции.");
   }

   void E1() {
       Error("Неожиданный вход в if-операторе.");
   }
   void E2() {
       Error("If-оператор незакончен.");
   }
   void E3() {
       Error("Лишняя правая скобка в выражении после И.");
   }

   void L() {
       Error("for-операторы вложены неверно. Пропущено next");
   }

   void M1() {
       Error("Неожиданный вход в if-операторе.");
   }
   void M2() {
       Error("If-оператор незакончен.");
   }
   void M3() {
       Error("Два знака отношения в if-операторе.");
   }
   void M4() {
       Error("Лишняя правая скобка в выражении после знака отношения.");
   }

   void N1() {
       Error("Пропущена правая скобка перед вход.");
   }
   void N2() {
       Error("Пропущена правая скобка в конце строки.");
   }

   void K() {
       Error("for-операторы вложены неверно - лишнее next.");
   }

   void P1() {
       Error("Неожиданный вход в for-операторе.");
   }
   void P2() {
       Error("for-оператор незакончен.");
   }
   void P3() {
       Error("Лишняя правая скобка в выражении после to.");
   }
   void P4() {
       Error("to пропущено или не на своём месте в for-операторе.");
   }

   void P() {
       Error("Программа продолжается после end-оператора.");
   }


   void T1() {
       Error("Нет программы.");
   }
   void T2() {
       Error("Пропущен end-оператор.");
   }
   void T3() {
       Error("Программа кончается посреди оператора.");
   }

   void O() {
       Error("Ошибка компилятора.");
   }

   void Create_Control_Table()
   {
       //<Программа>
       Control_Table[1][1] = &Syntax_analyzer::F1; 
       Control_Table[1][2] = &Syntax_analyzer::A; 
       Control_Table[1][3] = &Syntax_analyzer::A; 
       Control_Table[1][4] = &Syntax_analyzer::A;
       Control_Table[1][5] = &Syntax_analyzer::A;
       Control_Table[1][6] = &Syntax_analyzer::A;
       Control_Table[1][7] = &Syntax_analyzer::A;
       Control_Table[1][8] = &Syntax_analyzer::A;
       Control_Table[1][9] = &Syntax_analyzer::A;
       Control_Table[1][10] = &Syntax_analyzer::A;
       Control_Table[1][11] = &Syntax_analyzer::A;
       Control_Table[1][12] = &Syntax_analyzer::A;
       Control_Table[1][13] = &Syntax_analyzer::A;
       Control_Table[1][14] = &Syntax_analyzer::A;
       Control_Table[1][15] = &Syntax_analyzer::A;
       Control_Table[1][16] = &Syntax_analyzer::A;
       Control_Table[1][17] = &Syntax_analyzer::A;
       Control_Table[1][18] = &Syntax_analyzer::A;
       Control_Table[1][19] = &Syntax_analyzer::A; 
       Control_Table[1][20] = &Syntax_analyzer::A; 
       Control_Table[1][21] = &Syntax_analyzer::A;
       Control_Table[1][22] = &Syntax_analyzer::C;
       Control_Table[1][23] = &Syntax_analyzer::T1;

       //<Тело программы>
       Control_Table[2][1] = &Syntax_analyzer::F3;
       Control_Table[2][2] = &Syntax_analyzer::B;
       Control_Table[2][3] = &Syntax_analyzer::B;
       Control_Table[2][4] = &Syntax_analyzer::F2;
       Control_Table[2][5] = &Syntax_analyzer::F4;
       Control_Table[2][6] = &Syntax_analyzer::F9;
       Control_Table[2][7] = &Syntax_analyzer::F5;
       Control_Table[2][8] = &Syntax_analyzer::F7;
       Control_Table[2][9] = &Syntax_analyzer::B;
       Control_Table[2][10] = &Syntax_analyzer::B;
       Control_Table[2][11] = &Syntax_analyzer::F6;
       Control_Table[2][12] = &Syntax_analyzer::F8;
       Control_Table[2][13] = &Syntax_analyzer::F2;
       Control_Table[2][14] = &Syntax_analyzer::B;
       Control_Table[2][15] = &Syntax_analyzer::B;
       Control_Table[2][16] = &Syntax_analyzer::F12;
       Control_Table[2][17] = &Syntax_analyzer::B;
       Control_Table[2][18] = &Syntax_analyzer::B;
       Control_Table[2][19] = &Syntax_analyzer::B;
       Control_Table[2][20] = &Syntax_analyzer::B;
       Control_Table[2][21] = &Syntax_analyzer::B;
       Control_Table[2][22] = &Syntax_analyzer::C;
       Control_Table[2][23] = &Syntax_analyzer::T2;

       //<Шаг>
       Control_Table[3][1] = &Syntax_analyzer::F11;
       Control_Table[3][2] = &Syntax_analyzer::G1;
       Control_Table[3][3] = &Syntax_analyzer::G1;
       Control_Table[3][4] = &Syntax_analyzer::G1;
       Control_Table[3][5] = &Syntax_analyzer::G1;
       Control_Table[3][6] = &Syntax_analyzer::G1;
       Control_Table[3][7] = &Syntax_analyzer::G1;
       Control_Table[3][8] = &Syntax_analyzer::G1;
       Control_Table[3][9] = &Syntax_analyzer::G1;
       Control_Table[3][10] = &Syntax_analyzer::G2;
       Control_Table[3][11] = &Syntax_analyzer::G1;
       Control_Table[3][12] = &Syntax_analyzer::G1;
       Control_Table[3][13] = &Syntax_analyzer::G1;
       Control_Table[3][14] = &Syntax_analyzer::G1;
       Control_Table[3][15] = &Syntax_analyzer::F10;
       Control_Table[3][16] = &Syntax_analyzer::G1;
       Control_Table[3][17] = &Syntax_analyzer::G1;
       Control_Table[3][18] = &Syntax_analyzer::G1;
       Control_Table[3][19] = &Syntax_analyzer::G1;
       Control_Table[3][20] = &Syntax_analyzer::G1;
       Control_Table[3][21] = &Syntax_analyzer::G1;
       Control_Table[3][22] = &Syntax_analyzer::C;
       Control_Table[3][23] = &Syntax_analyzer::T2;

       //<Другие строки>
       Control_Table[4][1] = &Syntax_analyzer::F13;
       Control_Table[4][2] = &Syntax_analyzer::D;
       Control_Table[4][3] = &Syntax_analyzer::D;
       Control_Table[4][4] = &Syntax_analyzer::D;
       Control_Table[4][5] = &Syntax_analyzer::D;
       Control_Table[4][6] = &Syntax_analyzer::D;
       Control_Table[4][7] = &Syntax_analyzer::D;
       Control_Table[4][8] = &Syntax_analyzer::D;
       Control_Table[4][9] = &Syntax_analyzer::D;
       Control_Table[4][10] = &Syntax_analyzer::D;
       Control_Table[4][11] = &Syntax_analyzer::D;
       Control_Table[4][12] = &Syntax_analyzer::D;
       Control_Table[4][13] = &Syntax_analyzer::D;
       Control_Table[4][14] = &Syntax_analyzer::D;
       Control_Table[4][15] = &Syntax_analyzer::D;
       Control_Table[4][16] = &Syntax_analyzer::D;
       Control_Table[4][17] = &Syntax_analyzer::D;
       Control_Table[4][18] = &Syntax_analyzer::D;
       Control_Table[4][19] = &Syntax_analyzer::D;
       Control_Table[4][20] = &Syntax_analyzer::D;
       Control_Table[4][21] = &Syntax_analyzer::D;
       Control_Table[4][22] = &Syntax_analyzer::C;
       Control_Table[4][23] = &Syntax_analyzer::T2;

       //<Выражение>
       Control_Table[5][1] = &Syntax_analyzer::K2;
       Control_Table[5][2] = &Syntax_analyzer::F14;
       Control_Table[5][3] = &Syntax_analyzer::K1;
       Control_Table[5][4] = &Syntax_analyzer::K4;
       Control_Table[5][5] = &Syntax_analyzer::K4;
       Control_Table[5][6] = &Syntax_analyzer::K4;
       Control_Table[5][7] = &Syntax_analyzer::K1;
       Control_Table[5][8] = &Syntax_analyzer::K4;
       Control_Table[5][9] = &Syntax_analyzer::F14;
       Control_Table[5][10] = &Syntax_analyzer::K3;
       Control_Table[5][11] = &Syntax_analyzer::K4;
       Control_Table[5][12] = &Syntax_analyzer::K4;
       Control_Table[5][13] = &Syntax_analyzer::K4;
       Control_Table[5][14] = &Syntax_analyzer::K1;
       Control_Table[5][15] = &Syntax_analyzer::K1;
       Control_Table[5][16] = &Syntax_analyzer::K4;
       Control_Table[5][17] = &Syntax_analyzer::F15;
       Control_Table[5][18] = &Syntax_analyzer::F16;
       Control_Table[5][19] = &Syntax_analyzer::K5;
       Control_Table[5][20] = &Syntax_analyzer::K5;
       Control_Table[5][21] = &Syntax_analyzer::K5;
       Control_Table[5][22] = &Syntax_analyzer::C;
       Control_Table[5][23] = &Syntax_analyzer::T3;

       //<Терм>
       Control_Table[6][1] = &Syntax_analyzer::K2;
       Control_Table[6][2] = &Syntax_analyzer::F20;
       Control_Table[6][3] = &Syntax_analyzer::K1;
       Control_Table[6][4] = &Syntax_analyzer::K4;
       Control_Table[6][5] = &Syntax_analyzer::K4;
       Control_Table[6][6] = &Syntax_analyzer::K4;
       Control_Table[6][7] = &Syntax_analyzer::K1;
       Control_Table[6][8] = &Syntax_analyzer::K4;
       Control_Table[6][9] = &Syntax_analyzer::F20;
       Control_Table[6][10] = &Syntax_analyzer::K3;
       Control_Table[6][11] = &Syntax_analyzer::K4;
       Control_Table[6][12] = &Syntax_analyzer::K4;
       Control_Table[6][13] = &Syntax_analyzer::K4;
       Control_Table[6][14] = &Syntax_analyzer::K1;
       Control_Table[6][15] = &Syntax_analyzer::K1;
       Control_Table[6][16] = &Syntax_analyzer::K4;
       Control_Table[6][17] = &Syntax_analyzer::K6;
       Control_Table[6][18] = &Syntax_analyzer::K6;
       Control_Table[6][19] = &Syntax_analyzer::K6;
       Control_Table[6][20] = &Syntax_analyzer::K6;
       Control_Table[6][21] = &Syntax_analyzer::K6;
       Control_Table[6][22] = &Syntax_analyzer::C;
       Control_Table[6][23] = &Syntax_analyzer::T3;

       //<Множитель>
       Control_Table[7][1] = &Syntax_analyzer::K2;
       Control_Table[7][2] = &Syntax_analyzer::F24;
       Control_Table[7][3] = &Syntax_analyzer::K1;
       Control_Table[7][4] = &Syntax_analyzer::K4;
       Control_Table[7][5] = &Syntax_analyzer::K4;
       Control_Table[7][6] = &Syntax_analyzer::K4;
       Control_Table[7][7] = &Syntax_analyzer::K1;
       Control_Table[7][8] = &Syntax_analyzer::K4;
       Control_Table[7][9] = &Syntax_analyzer::F24;
       Control_Table[7][10] = &Syntax_analyzer::K3;
       Control_Table[7][11] = &Syntax_analyzer::K4;
       Control_Table[7][12] = &Syntax_analyzer::K4;
       Control_Table[7][13] = &Syntax_analyzer::K4;
       Control_Table[7][14] = &Syntax_analyzer::K1;
       Control_Table[7][15] = &Syntax_analyzer::K1;
       Control_Table[7][16] = &Syntax_analyzer::K4;
       Control_Table[7][17] = &Syntax_analyzer::K6;
       Control_Table[7][18] = &Syntax_analyzer::K6;
       Control_Table[7][19] = &Syntax_analyzer::K6;
       Control_Table[7][20] = &Syntax_analyzer::K6;
       Control_Table[7][21] = &Syntax_analyzer::K6;
       Control_Table[7][22] = &Syntax_analyzer::C;
       Control_Table[7][23] = &Syntax_analyzer::T3;

       //<первичное>
       Control_Table[8][1] = &Syntax_analyzer::K2;
       Control_Table[8][2] = &Syntax_analyzer::F28;
       Control_Table[8][3] = &Syntax_analyzer::K1;
       Control_Table[8][4] = &Syntax_analyzer::K4;
       Control_Table[8][5] = &Syntax_analyzer::K4;
       Control_Table[8][6] = &Syntax_analyzer::K4;
       Control_Table[8][7] = &Syntax_analyzer::K1;
       Control_Table[8][8] = &Syntax_analyzer::K4;
       Control_Table[8][9] = &Syntax_analyzer::F27;
       Control_Table[8][10] = &Syntax_analyzer::K3;
       Control_Table[8][11] = &Syntax_analyzer::K4;
       Control_Table[8][12] = &Syntax_analyzer::K4;
       Control_Table[8][13] = &Syntax_analyzer::K4;
       Control_Table[8][14] = &Syntax_analyzer::K1;
       Control_Table[8][15] = &Syntax_analyzer::K1;
       Control_Table[8][16] = &Syntax_analyzer::K4;
       Control_Table[8][17] = &Syntax_analyzer::K6;
       Control_Table[8][18] = &Syntax_analyzer::K6;
       Control_Table[8][19] = &Syntax_analyzer::K6;
       Control_Table[8][20] = &Syntax_analyzer::K6;
       Control_Table[8][21] = &Syntax_analyzer::K6;
       Control_Table[8][22] = &Syntax_analyzer::C;
       Control_Table[8][23] = &Syntax_analyzer::T3;

       //<E-список>
       Control_Table[9][1] = &Syntax_analyzer::F19;
       Control_Table[9][2] = &Syntax_analyzer::K7;
       Control_Table[9][3] = &Syntax_analyzer::F19;
       Control_Table[9][4] = &Syntax_analyzer::O;
       Control_Table[9][5] = &Syntax_analyzer::O;
       Control_Table[9][6] = &Syntax_analyzer::O;
       Control_Table[9][7] = &Syntax_analyzer::F19;
       Control_Table[9][8] = &Syntax_analyzer::O;
       Control_Table[9][9] = &Syntax_analyzer::K7;
       Control_Table[9][10] = &Syntax_analyzer::F19;
       Control_Table[9][11] = &Syntax_analyzer::O;
       Control_Table[9][12] = &Syntax_analyzer::O;
       Control_Table[9][13] = &Syntax_analyzer::O;
       Control_Table[9][14] = &Syntax_analyzer::F19;
       Control_Table[9][15] = &Syntax_analyzer::F19;
       Control_Table[9][16] = &Syntax_analyzer::O;
       Control_Table[9][17] = &Syntax_analyzer::F17;
       Control_Table[9][18] = &Syntax_analyzer::F18;
       Control_Table[9][19] = &Syntax_analyzer::O;
       Control_Table[9][20] = &Syntax_analyzer::O;
       Control_Table[9][21] = &Syntax_analyzer::O;
       Control_Table[9][22] = &Syntax_analyzer::O;
       Control_Table[9][23] = &Syntax_analyzer::O;

       //<T-список>
       Control_Table[10][1] = &Syntax_analyzer::F23;
       Control_Table[10][2] = &Syntax_analyzer::K7;
       Control_Table[10][3] = &Syntax_analyzer::F23;
       Control_Table[10][4] = &Syntax_analyzer::O;
       Control_Table[10][5] = &Syntax_analyzer::O;
       Control_Table[10][6] = &Syntax_analyzer::O;
       Control_Table[10][7] = &Syntax_analyzer::F23;
       Control_Table[10][8] = &Syntax_analyzer::O;
       Control_Table[10][9] = &Syntax_analyzer::K7;
       Control_Table[10][10] = &Syntax_analyzer::F23;
       Control_Table[10][11] = &Syntax_analyzer::O;
       Control_Table[10][12] = &Syntax_analyzer::O;
       Control_Table[10][13] = &Syntax_analyzer::O;
       Control_Table[10][14] = &Syntax_analyzer::F23;
       Control_Table[10][15] = &Syntax_analyzer::F23;
       Control_Table[10][16] = &Syntax_analyzer::O;
       Control_Table[10][17] = &Syntax_analyzer::F23;
       Control_Table[10][18] = &Syntax_analyzer::F23;
       Control_Table[10][19] = &Syntax_analyzer::F21;
       Control_Table[10][20] = &Syntax_analyzer::F22;
       Control_Table[10][21] = &Syntax_analyzer::O;
       Control_Table[10][22] = &Syntax_analyzer::O;
       Control_Table[10][23] = &Syntax_analyzer::O;

       //<F-список>
       Control_Table[11][1] = &Syntax_analyzer::F26;
       Control_Table[11][2] = &Syntax_analyzer::K7;
       Control_Table[11][3] = &Syntax_analyzer::F26;
       Control_Table[11][4] = &Syntax_analyzer::K4;
       Control_Table[11][5] = &Syntax_analyzer::K4;
       Control_Table[11][6] = &Syntax_analyzer::K4;
       Control_Table[11][7] = &Syntax_analyzer::F26;
       Control_Table[11][8] = &Syntax_analyzer::K4;
       Control_Table[11][9] = &Syntax_analyzer::K7;
       Control_Table[11][10] = &Syntax_analyzer::F26;
       Control_Table[11][11] = &Syntax_analyzer::K4;
       Control_Table[11][12] = &Syntax_analyzer::K4;
       Control_Table[11][13] = &Syntax_analyzer::K4;
       Control_Table[11][14] = &Syntax_analyzer::F26;
       Control_Table[11][15] = &Syntax_analyzer::F26;
       Control_Table[11][16] = &Syntax_analyzer::K4;
       Control_Table[11][17] = &Syntax_analyzer::F26;
       Control_Table[11][18] = &Syntax_analyzer::F26;
       Control_Table[11][19] = &Syntax_analyzer::F26;
       Control_Table[11][20] = &Syntax_analyzer::F26;
       Control_Table[11][21] = &Syntax_analyzer::F25;
       Control_Table[11][22] = &Syntax_analyzer::C;
       Control_Table[11][23] = &Syntax_analyzer::T2;

       //<Отношение>
       Control_Table[12][1] = &Syntax_analyzer::E2;
       Control_Table[12][2] = &Syntax_analyzer::E1;
       Control_Table[12][3] = &Syntax_analyzer::b;
       Control_Table[12][4] = &Syntax_analyzer::E1;
       Control_Table[12][5] = &Syntax_analyzer::E1;
       Control_Table[12][6] = &Syntax_analyzer::E1;
       Control_Table[12][7] = &Syntax_analyzer::E1;
       Control_Table[12][8] = &Syntax_analyzer::E1;
       Control_Table[12][9] = &Syntax_analyzer::E1;
       Control_Table[12][10] = &Syntax_analyzer::E3;
       Control_Table[12][11] = &Syntax_analyzer::E1;
       Control_Table[12][12] = &Syntax_analyzer::E1;
       Control_Table[12][13] = &Syntax_analyzer::E1;
       Control_Table[12][14] = &Syntax_analyzer::E1;
       Control_Table[12][15] = &Syntax_analyzer::E1;
       Control_Table[12][16] = &Syntax_analyzer::E1;
       Control_Table[12][17] = &Syntax_analyzer::E1;
       Control_Table[12][18] = &Syntax_analyzer::E1;
       Control_Table[12][19] = &Syntax_analyzer::E1;
       Control_Table[12][20] = &Syntax_analyzer::E1;
       Control_Table[12][21] = &Syntax_analyzer::E1;
       Control_Table[12][22] = &Syntax_analyzer::C;
       Control_Table[12][23] = &Syntax_analyzer::T3;

       //<Конец цикла>
       Control_Table[13][1] = &Syntax_analyzer::O;
       Control_Table[13][2] = &Syntax_analyzer::O;
       Control_Table[13][3] = &Syntax_analyzer::O;
       Control_Table[13][4] = &Syntax_analyzer::b;
       Control_Table[13][5] = &Syntax_analyzer::O;
       Control_Table[13][6] = &Syntax_analyzer::O;
       Control_Table[13][7] = &Syntax_analyzer::O;
       Control_Table[13][8] = &Syntax_analyzer::O;
       Control_Table[13][9] = &Syntax_analyzer::O;
       Control_Table[13][10] = &Syntax_analyzer::O;
       Control_Table[13][11] = &Syntax_analyzer::O;
       Control_Table[13][12] = &Syntax_analyzer::O;
       Control_Table[13][13] = &Syntax_analyzer::L;
       Control_Table[13][14] = &Syntax_analyzer::O;
       Control_Table[13][15] = &Syntax_analyzer::O;
       Control_Table[13][16] = &Syntax_analyzer::O;
       Control_Table[13][17] = &Syntax_analyzer::O;
       Control_Table[13][18] = &Syntax_analyzer::O;
       Control_Table[13][19] = &Syntax_analyzer::O;
       Control_Table[13][20] = &Syntax_analyzer::O;
       Control_Table[13][21] = &Syntax_analyzer::O;
       Control_Table[13][22] = &Syntax_analyzer::O;
       Control_Table[13][23] = &Syntax_analyzer::O;

       //<Переход>
       Control_Table[14][1] = &Syntax_analyzer::M2;
       Control_Table[14][2] = &Syntax_analyzer::M1;
       Control_Table[14][3] = &Syntax_analyzer::M3;
       Control_Table[14][4] = &Syntax_analyzer::M1;
       Control_Table[14][5] = &Syntax_analyzer::M1;
       Control_Table[14][6] = &Syntax_analyzer::M1;
       Control_Table[14][7] = &Syntax_analyzer::b;
       Control_Table[14][8] = &Syntax_analyzer::M1;
       Control_Table[14][9] = &Syntax_analyzer::M1;
       Control_Table[14][10] = &Syntax_analyzer::M4;
       Control_Table[14][11] = &Syntax_analyzer::M1;
       Control_Table[14][12] = &Syntax_analyzer::M1;
       Control_Table[14][13] = &Syntax_analyzer::M1;
       Control_Table[14][14] = &Syntax_analyzer::M1;
       Control_Table[14][15] = &Syntax_analyzer::M1;
       Control_Table[14][16] = &Syntax_analyzer::M1;
       Control_Table[14][17] = &Syntax_analyzer::M1;
       Control_Table[14][18] = &Syntax_analyzer::M1;
       Control_Table[14][19] = &Syntax_analyzer::M1;
       Control_Table[14][20] = &Syntax_analyzer::M1;
       Control_Table[14][21] = &Syntax_analyzer::M1;
       Control_Table[14][22] = &Syntax_analyzer::C;
       Control_Table[14][23] = &Syntax_analyzer::T3;

       //<Правая скобка>
       Control_Table[15][1] = &Syntax_analyzer::N2;
       Control_Table[15][2] = &Syntax_analyzer::N1;
       Control_Table[15][3] = &Syntax_analyzer::N1;
       Control_Table[15][4] = &Syntax_analyzer::N1;
       Control_Table[15][5] = &Syntax_analyzer::N1;
       Control_Table[15][6] = &Syntax_analyzer::N1;
       Control_Table[15][7] = &Syntax_analyzer::N1;
       Control_Table[15][8] = &Syntax_analyzer::N1;
       Control_Table[15][9] = &Syntax_analyzer::N1;
       Control_Table[15][10] = &Syntax_analyzer::a;
       Control_Table[15][11] = &Syntax_analyzer::N1;
       Control_Table[15][12] = &Syntax_analyzer::N1;
       Control_Table[15][13] = &Syntax_analyzer::N1;
       Control_Table[15][14] = &Syntax_analyzer::N1;
       Control_Table[15][15] = &Syntax_analyzer::N1;
       Control_Table[15][16] = &Syntax_analyzer::N1;
       Control_Table[15][17] = &Syntax_analyzer::N1;
       Control_Table[15][18] = &Syntax_analyzer::N1;
       Control_Table[15][19] = &Syntax_analyzer::N1;
       Control_Table[15][20] = &Syntax_analyzer::N1;
       Control_Table[15][21] = &Syntax_analyzer::N1;
       Control_Table[15][22] = &Syntax_analyzer::C;
       Control_Table[15][23] = &Syntax_analyzer::T3;

       //<Конец>
       Control_Table[16][1] = &Syntax_analyzer::O;
       Control_Table[16][2] = &Syntax_analyzer::O;
       Control_Table[16][3] = &Syntax_analyzer::O;
       Control_Table[16][4] = &Syntax_analyzer::K;
       Control_Table[16][5] = &Syntax_analyzer::O;
       Control_Table[16][6] = &Syntax_analyzer::O;
       Control_Table[16][7] = &Syntax_analyzer::O;
       Control_Table[16][8] = &Syntax_analyzer::O;
       Control_Table[16][9] = &Syntax_analyzer::O;
       Control_Table[16][10] = &Syntax_analyzer::O;
       Control_Table[16][11] = &Syntax_analyzer::O;
       Control_Table[16][12] = &Syntax_analyzer::O;
       Control_Table[16][13] = &Syntax_analyzer::a;
       Control_Table[16][14] = &Syntax_analyzer::O;
       Control_Table[16][15] = &Syntax_analyzer::O;
       Control_Table[16][16] = &Syntax_analyzer::O;
       Control_Table[16][17] = &Syntax_analyzer::O;
       Control_Table[16][18] = &Syntax_analyzer::O;
       Control_Table[16][19] = &Syntax_analyzer::O;
       Control_Table[16][20] = &Syntax_analyzer::O;
       Control_Table[16][21] = &Syntax_analyzer::O;
       Control_Table[16][22] = &Syntax_analyzer::O;
       Control_Table[16][23] = &Syntax_analyzer::O;

       //<До>
       Control_Table[17][1] = &Syntax_analyzer::P2;
       Control_Table[17][2] = &Syntax_analyzer::P1;
       Control_Table[17][3] = &Syntax_analyzer::P1;
       Control_Table[17][4] = &Syntax_analyzer::P1;
       Control_Table[17][5] = &Syntax_analyzer::P1;
       Control_Table[17][6] = &Syntax_analyzer::P1;
       Control_Table[17][7] = &Syntax_analyzer::P1;
       Control_Table[17][8] = &Syntax_analyzer::P1;
       Control_Table[17][9] = &Syntax_analyzer::P1;
       Control_Table[17][10] = &Syntax_analyzer::P3;
       Control_Table[17][11] = &Syntax_analyzer::P1;
       Control_Table[17][12] = &Syntax_analyzer::P1;
       Control_Table[17][13] = &Syntax_analyzer::P1;
       Control_Table[17][14] = &Syntax_analyzer::a;
       Control_Table[17][15] = &Syntax_analyzer::P4;
       Control_Table[17][16] = &Syntax_analyzer::P1;
       Control_Table[17][17] = &Syntax_analyzer::P1;
       Control_Table[17][18] = &Syntax_analyzer::P1;
       Control_Table[17][19] = &Syntax_analyzer::P1;
       Control_Table[17][20] = &Syntax_analyzer::P1;
       Control_Table[17][21] = &Syntax_analyzer::P1;
       Control_Table[17][22] = &Syntax_analyzer::C;
       Control_Table[17][23] = &Syntax_analyzer::T3;

       //<@>
       Control_Table[18][1] = &Syntax_analyzer::P;
       Control_Table[18][2] = &Syntax_analyzer::P;
       Control_Table[18][3] = &Syntax_analyzer::P;
       Control_Table[18][4] = &Syntax_analyzer::P;
       Control_Table[18][5] = &Syntax_analyzer::P;
       Control_Table[18][6] = &Syntax_analyzer::P;
       Control_Table[18][7] = &Syntax_analyzer::P;
       Control_Table[18][8] = &Syntax_analyzer::P;
       Control_Table[18][9] = &Syntax_analyzer::P;
       Control_Table[18][10] = &Syntax_analyzer::P;
       Control_Table[18][11] = &Syntax_analyzer::P;
       Control_Table[18][12] = &Syntax_analyzer::P;
       Control_Table[18][13] = &Syntax_analyzer::P;
       Control_Table[18][14] = &Syntax_analyzer::P;
       Control_Table[18][15] = &Syntax_analyzer::P;
       Control_Table[18][16] = &Syntax_analyzer::P;
       Control_Table[18][17] = &Syntax_analyzer::P;
       Control_Table[18][18] = &Syntax_analyzer::P;
       Control_Table[18][19] = &Syntax_analyzer::P;
       Control_Table[18][20] = &Syntax_analyzer::P;
       Control_Table[18][21] = &Syntax_analyzer::P;
       Control_Table[18][22] = &Syntax_analyzer::C;
       Control_Table[18][23] = &Syntax_analyzer::c;

       for (int i = 1; i < 24; i++)
           Control_Table[19][i] = &Syntax_analyzer::d;

       for (int i = 1; i < 24; i++)
           Control_Table[20][i] = &Syntax_analyzer::e;

       for (int i = 1; i < 24; i++)
           Control_Table[21][i] = &Syntax_analyzer::f;

       for (int i = 1; i < 24; i++)
           Control_Table[22][i] = &Syntax_analyzer::g;

       for (int i = 1; i < 24; i++)
           Control_Table[23][i] = &Syntax_analyzer::h;

       for (int i = 1; i < 24; i++)
           Control_Table[24][i] = &Syntax_analyzer::i;

       for (int i = 1; i < 24; i++)
           Control_Table[25][i] = &Syntax_analyzer::j;

       for (int i = 1; i < 24; i++)
           Control_Table[26][i] = &Syntax_analyzer::k;

       for (int i = 1; i < 24; i++)
           Control_Table[27][i] = &Syntax_analyzer::l;

       for (int i = 1; i < 24; i++)
           Control_Table[28][i] = &Syntax_analyzer::m;

       for (int i = 1; i < 24; i++)
           Control_Table[29][i] = &Syntax_analyzer::n;

       for (int i = 1; i < 24; i++)
           Control_Table[30][i] = &Syntax_analyzer::o;

       for (int i = 1; i < 24; i++)
           Control_Table[31][i] = &Syntax_analyzer::p;

       for (int i = 1; i < 24; i++)
           Control_Table[32][i] = &Syntax_analyzer::q;

       for (int i = 1; i < 24; i++)
           Control_Table[33][i] = &Syntax_analyzer::r;
   };

};

