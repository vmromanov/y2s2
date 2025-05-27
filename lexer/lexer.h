#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "locale.h"
#include <unordered_map>
#include <vector>
#include <iomanip>
#include "LexConst.h"
#include "HASH.h"
using namespace std;
#pragma once
ostream& operator<<(ostream& os, const Hash& hash) {
    // Çàãîëîâîê òàáëèöû
    os << left
        << setw(10) << "Èíäåêñ"
        << setw(10) << "Ìåòêà"
        << setw(10) << "TL"
        << setw(10) << "Ñëåäóþùèé"
        << endl;

    // Ðàçäåëèòåëü
    os << setfill('-') << setw(40) << "" << setfill(' ') << endl;

    os << left
        << setw(10) << "0"
        << setw(10) << hash.t[0].label
        << setw(10) << hash.t[0].index_el
        << setw(10) << hash.t[0].next
        << endl;

    // Ïå÷àòàåì îñòàëüíûå ýëåìåíòû
    for (int i = 1; i < hash.nts; ++i) {
        if (hash.t[i].label != -1) {
            os << left
                << setw(10) << i
                << setw(10) << hash.t[i].label
                << setw(10) << hash.t[i].index_el
                << setw(10) << hash.t[i].next
                << endl;
        }
    }

    return os;
}
enum R_simb
{
    letter1,
    digit,
    ar_op,
    attit, // îòíîøåíèå 
    l_bracket,
    r_bracket,
    point,
    space,
    CR,
    end,
    other
};
enum RKL
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


class Analyzator
{
private:
    vector<string> errors;
    int current_line;         // Òåêóùèé íîìåð ñòðîêè
    string last_error_message; // Ñîîáùåíèå îá îøèáêå
    fstream file_errors;
    string str;
    typedef void(Analyzator::* pfuncType)();//óêàçàòåëü íà ôóíêèöþ ñîñòîÿíèÿ
    pfuncType pfunc;
    int RCH, // ðåãèñòð ÷èñëà
        RZ, // ðåãèñòð çíàêà
        RP, // ðåãèñòð ïîðÿäêà
        RS, // ðåãèñòð ñ÷åò÷èêà
        RKL,// ðåãèñòð êëàññà ëåêñåì 
        ROT,// ðåãèñòðï çíà÷åíèÿ îòíîøåíèÿ  
        RZN,// ðåãèñòð çíà÷åíèÿ ñèìâîëà
        RSOS,//  ðåãèñòð ñîñòîÿíèÿ 
        ROB,// ðåãèñòð îáíàðóæåíèÿ
        RK,// ðåãèñòð çíà÷åíèÿ êëàññà ñèìâîëà  
        RSTR,// ðåãèñòð ñòðîêè 
        RI,// ðåãèñòð íîìåðà áóêâû â èìåíè ïåðåìåííîé 
        RSE; // ðåãèñòð ñ÷åò÷èêà îøèáîê
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
        case CR:
            break;
        default:
            last_error_message = "íåò íà÷àëüíîé ìåòêè";
            RSE++;
            G1b();
        }
    }
    void A2()
    {
        switch (RK)
        {
        case letter1:
            C2a();
            break;
        case digit:
            D1a();
            break;
        case ar_op:
            A2a();
            break;
        case attit:
            H1a();
            break;
        case l_bracket:
            A2h();
            break;
        case r_bracket:
            A3b();
            break;
        case point:
            D6b();
            break;
        case space:
            break;
        case CR:
            pfunc = &Analyzator::A1;
            break;
        default:
            last_error_message = "íåêîððåêòíîå ïðèñâàèâàíèå ";
            RSE++;
            G1b();
        }
    }
    void A3()
    {
        switch (RK)
        {
        case letter1:
            B1a();
            break;
        case digit:
            D1a();
            break;
        case ar_op:
            A2a();
            break;
        case attit:
            H1a();
            break;
        case l_bracket:
            A2h();
            break;
        case r_bracket:
            A3b();
            break;
        case point:
            D6b();
            break;
        case space:
            break;
        case CR:
            pfunc = &Analyzator::A1;
            break;
        default:
            last_error_message = "íåêîððåêòíûé ñèìâîë/ñèìâîëû ";
            RSE++;
            G1b();
            
        }
    }
    void B1()
    {
        switch (RK)
        {
        case letter1:
            M1();
            break;
        case space:
            break;
        case CR:
            A1f();
            break;
        default:
            last_error_message = "íåêîððåêòíûé ñèìâîë/ñèìâîëû ";
            RSE++;
            G1b();
        }
    }
    void C1()
    {
        switch (RK)
        {
        case letter1:
            C2d();
            break;
        case space:
            break;
        default:
            last_error_message = "íåêîððåêòíàÿ ìåòêà ïîñëå êëþ÷åâîãî ñëîâà ";
            RSE++;
            G1b();
        }
    }
    void C2()
    {
        switch (RK)
        {
        case letter1:
            B1b();
            break;
        case digit:
            A3a();
            break;
        case ar_op:
            A2g();
            break;
        case attit:
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
        case CR:
            A1a();
            break;
        default:
            last_error_message = "íåêîððåêòíûé ñèìâîë/ñèìâîëû";
            RSE++;
            G1b();

        }
    }
    void D1()
    {
        switch (RK)
        {
        case letter1:
            M2();
            break;
        case digit:
            D1b();
            break;
        case ar_op:
            A2c();
            break;
        case attit:
            H1c();
            break;
        case l_bracket:
            A2l();
            break;
        case r_bracket:
            A3d();
            break;
        case point:
            D2c();
            break;
        case space:
            break;
        case CR:
            A1b();
            break;
        default:
            last_error_message = "íåêîððåêòíûé ñèìâîë/ñèìâîëû";
            RSE++;
            G1b();
        }
    }
    void D2()
    {
        switch (RK)
        {
        case letter1:
            M3();
            break;
        case digit:
            D2a();
            break;
        case ar_op:
            A2c();
        case attit:
            H1c();
        case l_bracket:
            A2l();
        case r_bracket:
            A3d();
            break;
        case space:
            break;
        case CR:
            A1c();
            break;
        default:
            last_error_message = "íåêîððåêòíûé ñèìâîë/ñèìâîëû";
            RSE++;
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
        case ar_op:
            D4a();
            break;
        case space:
            break;
        default:
            last_error_message = "íåêîððåêòíûé ñèìâîë/ñèìâîëû";
            RSE++;
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
            last_error_message = "íåêîððåêòíûé ñèìâîë/ñèìâîëû";
            RSE++;
            G1b();
        }
    }
    void D5()
    {
        switch (RK)
        {
        case letter1:
            B1c();
            break;
        case digit:
            D5c();
            break;
        case attit:
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
        case CR:
            A1d();
            break;
        default:
            last_error_message = "íåêîððåêòíûé ñèìâîë/ñèìâîëû";
            RSE++;
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
            last_error_message = "íåêîððåêòíûé ñèìâîë/ñèìâîëû";
            RSE++;
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
            last_error_message = "íåêîððåêòíûé ñèìâîë/ñèìâîëû";
            RSE++;
            G1b();
        }
    }
    void E2()
    {
        switch (RK)
        {
        case letter1:
            B1e();
            break;
        case digit:
            E2c();
            break;
        case attit:
            H1f();
            break;
        case space:
            break;
        case ar_op:
            A2f();
            break;
        case l_bracket:
            A2j();
            break;
        case r_bracket:
            A3g();
        case CR:
            A1e();
            break;
        default:
            last_error_message = "íåêîððåêòíûé ñèìâîë/ñèìâîëû";
            RSE++;
            G1b();

        }
    }
    void F1()
    {
        switch (RK)
        {
        case letter1:
            F2a();
            break;
        case space:
            break;
        default:
            last_error_message = "íåêîððåêòíûé ñèìâîë/ñèìâîëû";
            RSE++;
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
        case attit:
            A2o();
            break;
        case space:
            break;
        default:
            last_error_message = "íåêêîðåêòíîå îáúÿâëåíèå ïåðåìåííîé: â èìåíè ïåðåìåííîé ìîæåò õðàíèòñÿ òîëüêî 1 áóêâà";
            RSE++;
            G1b();


        }
    }
    void F3()
    {
        switch (RK)
        {
        case attit:
            A2o();
            break;
        case space:
            break;
        default:
            last_error_message = "íåêêîðåêòíîå îáúÿâëåíèå ïåðåìåííîé: â èìåíè ïåðåìåííîé ìîæåò õðàíèòñÿ òîëüêî 1 öèôðà ";
            RSE++;
            G1b();
        }
    }
    void G1()
    {
        switch (RK)
        {
        case CR:
            pfunc = &Analyzator::A1;
            break;
        default:
            pfunc = &Analyzator::G1;
        }
    }
    void H1()
    {
        switch (RK)
        {
        case letter1:
            C2b();
            break;
        case digit:
            D1c();
            break;
        case ar_op:
            A2g();
            break;
        case attit:
            A2p();
            break;
        case l_bracket:
            A2k();
            break;
        case r_bracket:
            A3c();
            break;
        case point:
            D6a();
            break;
        case space:
            break;
        case CR:
            A1a();
            break;
        default:
            last_error_message = "íåêîððåêòíûé ñèìâîë/ñèìâîëû ";
            RSE++;
            G1b();
        }
    }
    void transliterator(char ch)
    {
        if (ch >= 'a' && ch <= 'z')
        {
            RK = letter1;
            RZN = ch - 'a' + 1;
        }
        else if (ch >= 'A' && ch <= 'Z')
        {
            RK = letter1;
            RZN = ch - 'A';
        }
        else if (ch >= '0' && ch <= '9')
        {
            RK = digit;
            RZN = ch - '0';
        }
        else if (ch == '+')
        {
            RK = ar_op;
            RZN = 1;
        }
        else if (ch == '-')
        {
            RK = ar_op;
            RZN = 2;
        }
        else if (ch == '*')
        {
            RK = ar_op;
            RZN = 3;
        }
        else if (ch == '/')
        {
            RK = ar_op;
            RZN = 4;
        }
        else if (ch == '^')
        {
            RK = ar_op;
            RZN = 5;
        }
        else if (ch == ' ' || ch == '\t')
        {
            RK = space;
        }
        else if (ch == '.')
        {
            RK = point;
        }
        else if (ch == '\n')
        {
            RK = CR;
        }
        else if (ch == '(')
        {
            RK = l_bracket;
        }
        else if (ch == ')')
        {
            RK = r_bracket;
        }
        else if (ch == '=')
        {
            RK = attit;
            RZN = 1;
        }
        else if (ch == '<')
        {
            RK = attit;
            RZN = 2;
        }
        else if (ch == '>')
        {
            RK = attit;
            RZN = 3;
        }
        else {
            RK = other;
            G1b();
        }
    }
    void Parse()
    {
        for (int i = 0; i < str.size(); ++i)
        {
            transliterator(str[i]);
            (this->*pfunc)();
        }
    }
    void End()
    {
        if (pfunc == &Analyzator::A1 || pfunc == &Analyzator::A2 || pfunc == &Analyzator::A3 || pfunc == &Analyzator::G1)
        {
            pfunc = &Analyzator::exit1;
        }
        else
            if (pfunc == &Analyzator::C1 || pfunc == &Analyzator::D1)
            {
                pfunc = &Analyzator::exit3;
            }
            else
                if (pfunc == &Analyzator::C2 || pfunc == &Analyzator::D2)
                {
                    pfunc = &Analyzator::exit4;
                }
                else
                    if (pfunc == &Analyzator::H1)
                    {
                        pfunc = &Analyzator::exit2;
                    }
                    else
                        if (pfunc == &Analyzator::D5)
                        {
                            pfunc = &Analyzator::exit5;
                        }
                        else
                            pfunc = &Analyzator::error2;
        (this->*pfunc)();
        PrintLexem();
        PrintOperation();
        PrintTS();
        PrintErrors();
        file_errors.close();
    }
    void AddLexeme()
    {
        Lexeme t;
        t.TokenClass = RKL;
        t.TokenValue = -1;
        if (RKL == _ERROR) {
            string error_msg = "Â ñòðîêå " + to_string(current_line) + " îøèáêà: " + last_error_message;
            errors.push_back(error_msg);
            file_errors << "Â ñòðîêå " << current_line
                << " îøèáêà: " << last_error_message << endl;
            return;
        }
        if (RKL == ROWLABEL || RKL == GOTO || RKL == GOSUB) {
            if (RKL == GOTO || RKL == GOSUB)
            {
                if (TS.Find(RSTR) == -1)
                {
                    TS.el_add(RSTR, -1);
                }

            }
            else
            {
                if (RSTR == 2000)
                {
                    cout << endl << endl;
                    int x = 0;
                    x++;
                }

                int le=TS.Find(RSTR);
                if ((le != -1 && TS.TLinf(le) == -1))
                    TS.el_del(RSTR);
                TS.el_add(RSTR, NTL);
            }

            // Ïîëó÷àåì èíäåêñ èç TS ÷åðåç õåø-òàáëèöó
            t.TokenValue = TS.Find(RSTR);
            RSTR = 0; // Ñáðîñ ðåãèñòðà ñòðîêè
            
        }

            if (RKL == OPERAND || RKL == NEXT) {
                if (RI != 0) { // Èäåíòèôèêàòîð
                    int n = (RK == digit) ? (RI + 26 * (RZN + 1)) : RI;
                    TO[n] = 1;
                    t.TokenValue = n;
                    RI = 0;
                }
                else { // Êîíñòàíòà
                    double value = RCH * pow(10, RZ * (RP - RS)); // Âû÷èñëåíèå çíà÷åíèÿ
                    // Ïîèñê ñóùåñòâóþùåé êîíñòàíòû â TO
                    bool found = false;
                    for (int i = 287; i < NTO; ++i) {
                        if (TO[i] == value) {
                            t.TokenValue = i;
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        TO[NTO] = value;
                        t.TokenValue = NTO;
                        NTO++;
                    }
                    // Ñáðîñ ðåãèñòðîâ
                    RCH = RP = RS = 0;
                    RZ = 1;
                }
                
            }
        if (RKL == LET || RKL == FOR)
        {
            TO[RI] = 1;
            t.TokenValue = RI;
            RI = 0;
           
        }
        if (RKL == AR_OP)
        {
            t.TokenValue = RZN;
            
        }
        if (RKL == ATTIT)
        {
            t.TokenValue = ROT;
           
        }
        TL[NTL] = t;
        NTL++;
    }
    void PrintErrors() {
        if (!errors.empty()) {
            cout << "\nÑïèñîê îøèáîê:\n";
            cout << "--------------------------------------\n";
            for (const auto& error : errors) {
                cout << error << endl;
            }
            cout << "--------------------------------------\n";
        }
        else {
            cout << "\nÎøèáîê íå îáíàðóæåíî.\n";
        }
    }
    void PrintLexem()
    {
        cout << "Òàáëèöà ëåêñåì:" << endl;
        cout << left << setw(5) << "¹" << setw(15) << "Òèï ëåêñåìû" << setw(10) << "Çíà÷åíèå" << endl;
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
            fout << i - 1 << "   " << Tclass[TL[i].TokenClass - 1] << "  " << TL[i].TokenValue << endl;

            // Âûâîäèì â êîíñîëü ñ âûðàâíèâàíèåì
            cout << left << setw(5) << i
                << setw(15) << Tclass[TL[i].TokenClass - 1]
                << setw(10) << TL[i].TokenValue << endl;
        }
        fout.close();
    }


    void PrintOperation()
    {
        cout << endl;
        cout << "Òàáëèöà îïåðàíäîâ:" << endl;
        cout << left << setw(5) << "¹" << setw(15) << "Îïåðàíä" << endl;
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

                // Âûâîäèì â êîíñîëü ñ âûðàâíèâàíèåì
                cout << left << setw(5) << i
                    << setw(15) << TO[i] << endl;
            }
        }

        for (int i = 287; i < NTO; ++i)
        {
            fout.width(3);
            fout << i << " " << TO[i] << endl;

            // Âûâîäèì â êîíñîëü ñ âûðàâíèâàíèåì
            cout << left << setw(5) << i
                << setw(15) << TO[i] << endl;
        }
        fout.close();
    }


    void PrintTS() {
        cout << "Òàáëèöà ìåòîê:" << endl;
        ofstream fout("result_label.txt");
        TS.print(fout);
        cout << TS << endl;
    }


public:
    Analyzator() :
        start_vector(26, 0),
        table_alternatives(26),
        TL(256),
        TS(256),
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
        memset(TO, 0, sizeof(TO));
        InitializeStartVector();
        InitializeTable();
        pfunc = &Analyzator::A1;
    }

    // Ôóíêöèÿ äëÿ èíèöèàëèçàöèè start_vector
    void InitializeStartVector() {
        start_vector.resize(26);
        start_vector['E' - 'A'] = 0;    // END
        start_vector['F' - 'A'] = 2;    // FOR
        start_vector['G' - 'A'] = 4;    // GOTO, GOSUB
        start_vector['I' - 'A'] = 10;   // IF
        start_vector['L' - 'A'] = 11;   // LET
        start_vector['N' - 'A'] = 13;   // NEXT
        start_vector['R' - 'A'] = 17;   // RETURN, REM
        start_vector['S' - 'A'] = 22;   // STEP
        start_vector['T' - 'A'] = 25;   // TO
    }

        // Ôóíêöèÿ äëÿ èíèöèàëèçàöèè òàáëèöû
    void InitializeTable() {

        for (int i = 0; i < 26; ++i) {
            table_alternatives[i].alternative = -1;					// Íåò àëüòåðíàòèâ ïî óìîë÷àíèþ
            table_alternatives[i].pfunc = &Analyzator::next;   // Ïî óìîë÷àíèþ ôóíêöèÿ "next"
        }

        table_alternatives[0].letter = 'N' - 'A';
        table_alternatives[1].letter = 'D' - 'A';
        table_alternatives[1].pfunc = &Analyzator::A2q; // Ôóíêöèÿ äëÿ END 
        table_alternatives[2].letter = 'O' - 'A';
        table_alternatives[3].letter = 'R' - 'A';
        table_alternatives[3].pfunc = &Analyzator::F1b; // Ôóíêöèÿ äëÿ FOR 
        table_alternatives[4].letter = 'O' - 'A';
        table_alternatives[5].alternative = 7;		   // àëüòåðíàòèâà - GOSUB
        table_alternatives[5].letter = 'T' - 'A';
        table_alternatives[6].letter = 'O' - 'A';
        table_alternatives[6].pfunc = &Analyzator::E1a; //ôóíêöèÿ äëÿ GOTO
        table_alternatives[7].letter = 'S' - 'A';
        table_alternatives[8].letter = 'U' - 'A';
        table_alternatives[9].letter = 'B' - 'A';
        table_alternatives[9].pfunc = &Analyzator::E1b; // ôóíêöèÿ äëÿ GOSUB
        table_alternatives[10].letter = 'F' - 'A';
        table_alternatives[10].pfunc = &Analyzator::A2r; // Ôóíêöèÿ äëÿ IF 
        table_alternatives[11].letter = 'E' - 'A';
        table_alternatives[12].letter = 'T' - 'A';
        table_alternatives[12].pfunc = &Analyzator::F1a; // Ôóíêöèÿ äëÿ LET
        table_alternatives[13].letter = 'E' - 'A';
        table_alternatives[14].letter = 'X' - 'A';
        table_alternatives[15].letter = 'T' - 'A';
        table_alternatives[15].pfunc = &Analyzator::C1a; // Ôóíêöèÿ äëÿ NEXT
        table_alternatives[16].letter = 'E' - 'A';
        table_alternatives[17].letter = 'T' - 'A';
        table_alternatives[17].alternative = 21;
        table_alternatives[18].letter = 'U' - 'A';
        table_alternatives[19].letter = 'R' - 'A';
        table_alternatives[20].letter = 'N' - 'A';
        table_alternatives[20].pfunc = &Analyzator::A2s; // Ôóíêöèÿ äëÿ RETURN
        table_alternatives[21].letter = 'M' - 'A';
        table_alternatives[21].pfunc = &Analyzator::G1a; // Ôóíêöèÿ äëÿ REM
        table_alternatives[22].letter = 'T' - 'A';
        table_alternatives[23].letter = 'E' - 'A';
        table_alternatives[24].letter = 'P' - 'A';
        table_alternatives[24].pfunc = &Analyzator::A2t; // Ôóíêöèÿ äëÿ STEP
        table_alternatives[25].letter = 'O' - 'A';
        table_alternatives[25].pfunc = &Analyzator::A2u; // Ôóíêöèÿ äëÿ TO
    }
    void start(const char* filename)
    {
        ifstream fin(filename);
        int line_number = 0;
        if (!fin)
        {
            throw 1;
        }
        while (!fin.eof()) {
            str.clear();
            getline(fin, str);
            line_number++;
            current_line=line_number; // Óñòàíàâëèâàåì òåêóùóþ ñòðîêó
            str += '\n';
            Parse();
        }
        End();
        fin.close();
    }
    Hash TS;
    struct Lexeme
    {
        int TokenClass;
        int TokenValue;
    };
    vector <Lexeme> TL;//âåêòîð òàáëèöû ëåêñåì òèïà êëàññà òîêåíà
    double TO[1024]; //òàáëèöà îïåðàíäîâ 
    int NTO;// óêàçàòåëü íà ïåðâûé ñâîáîäíûé ýëåìåíò â TO
    int NTS; // óêàçàòåëü íà ïåðâûé ñâîáîäíûé ýëåìåíò â TS
    int NTL;// óêàçàòåëü íà ïåðâûé ñâîáîäíûé ýëåìåíò â TL
    struct node
    {
        int letter;
        int alternative;
        void(Analyzator::* pfunc)();
    };
    vector<node> table_alternatives;//òàáëèöà äëÿ ðàñïîçíîâàíèÿ 
    void next()
    {
        ROB++;
    }
    void A1a()
    {
        AddLexeme();
        pfunc = &Analyzator::A1;
    }
    void A1b()
    {
        RP = 0;
        AddLexeme();
        pfunc = &Analyzator::A1;
    }
    void A1c()
    {
        AddLexeme();
        pfunc = &Analyzator::A1;
    }
    void A1d()
    {
        AddLexeme();
        pfunc = &Analyzator::A1;
    }
    void A1e()
    {
        A1a();
        pfunc = &Analyzator::A1;
    }
    void A1f()
    {
        RKL = _ERROR;
        AddLexeme();
        pfunc = &Analyzator::A1;
    }
    void A2a()
    {
        RKL = AR_OP;
        AddLexeme();
        pfunc = &Analyzator::A2;
    }
    void A2b()
    {
        AddLexeme();
        pfunc = &Analyzator::A2;
    }
    void A2c()
    {
        AddLexeme();
        RKL = AR_OP;
        AddLexeme();
        pfunc = &Analyzator::A2;
    }
    void A2h()
    {
        RKL = L_BRACKET;
        AddLexeme();
        pfunc = &Analyzator::A2;
    }
    void A2l()
    {
        AddLexeme();
        RKL = L_BRACKET;
        AddLexeme();
        pfunc = &Analyzator::A2;
    }
    void A2g()
    {
        AddLexeme();
        RKL = AR_OP;
        AddLexeme();
        pfunc = &Analyzator::A2;
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
        AddLexeme();
        pfunc = &Analyzator::A2;
    }
    void A2r()
    {
        RKL = IF;
        A2b();
        pfunc = &Analyzator::A2;
    }
    void A2k()
    {
        AddLexeme();
        RKL = L_BRACKET;
        AddLexeme();
        pfunc = &Analyzator::A2;
    }
    void A2s()
    {
        RKL = RETURN;
        A2b();
        pfunc = &Analyzator::A2;
    }
    void A2q()
    {
        RKL = END;
        A2b();
        pfunc = &Analyzator::A2;
    }
    void A2o()
    {
        if (RZN == 1)
        {
            AddLexeme();
        }
        else
        {
            G1b();
            return;
        }
        pfunc = &Analyzator::A2;
    }
    void A2u()
    {
        RKL = _TO;
        A2b();
        pfunc = &Analyzator::A2;
    }
    void A2j()
    {
        AddLexeme();
        RKL = L_BRACKET;
        AddLexeme();
        pfunc = &Analyzator::A2;
    }
    void A2f()
    {
        AddLexeme();
        RKL = AR_OP;
        AddLexeme();
        pfunc = &Analyzator::A2;
    }
    void A2t()
    {
        RKL = STEP;
        A2b();
        pfunc = &Analyzator::A2;
    }
    void A3a()
    {
        AddLexeme();
        pfunc = &Analyzator::A3;
    }
    void A3b()
    {
        RKL = R_BRACKET;
        AddLexeme();
        pfunc = &Analyzator::A3;
    }
    void A3c()
    {
        AddLexeme();
        RKL = R_BRACKET;
        AddLexeme();
        pfunc = &Analyzator::A3;
    }
    void A3d()
    {
        AddLexeme();
        RKL = R_BRACKET;
        AddLexeme();
        pfunc = &Analyzator::A3;
    }
    void A3g()
    {
        AddLexeme();
        RKL = R_BRACKET;
        AddLexeme();
        pfunc = &Analyzator::A3;
    }
    void B1a()
    {
        ROB = start_vector[RZN];
        pfunc = &Analyzator::B1;
    }
    void B1b()
    {
        AddLexeme();
        ROB = start_vector[RZN];
        pfunc = &Analyzator::B1;
    }
    void B1c()
    {
        AddLexeme();
        ROB = start_vector[RZN];
        pfunc = &Analyzator::B1;
    }
    void B1e()
    {
        AddLexeme();
        ROB = start_vector[RZN];
        pfunc = &Analyzator::B1;
    }
    void C1a()
    {
        RKL = NEXT;
        pfunc = &Analyzator::C1;
    }
    void C2a()
    {
        RKL = OPERAND;
        RI = RZN;
        pfunc = &Analyzator::C2;
    }
    void C2b()
    {
        AddLexeme();
        RKL = OPERAND;
        RI = RZN;
        pfunc = &Analyzator::C2;
    }
    void C2d()
    {
        RI = RZN;
        pfunc = &Analyzator::C2;
    }
    void D1a()
    {
        RKL = OPERAND;
        RCH = RZN;
        pfunc = &Analyzator::D1;
    }
    void D1b()
    {
        RCH *= 10;
        RCH += RZN;
        pfunc = &Analyzator::D1;
    }
    void D1c()
    {
        AddLexeme();
        RKL = OPERAND;
        RCH = RZN;
        pfunc = &Analyzator::D1;
    }
    void D2a()
    {
        RS++;
        RCH *= 10;
        RCH += RZN;
        pfunc = &Analyzator::D2;
    }
    void D2b()
    {
        RS = 1;
        RCH = RZN;
        pfunc = &Analyzator::D2;
    }
    void D2c()
    {
        RS = 0;
        pfunc = &Analyzator::D2;
    }
    void D3a()
    {
        RS = 0;
        pfunc = &Analyzator::D3;
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
        pfunc = &Analyzator::D4;
    }
    void D5a()
    {
        RZ = 1;
        RP = RZN;
        pfunc = &Analyzator::D5;
    }
    void D5b()
    {
        RP = RZN;
        pfunc = &Analyzator::D5;
    }
    void D5c()
    {
        RP *= 10;
        RP += RZN;
        pfunc = &Analyzator::D5;
    }
    void D6a()
    {
        AddLexeme();
        RKL = OPERAND;
        pfunc = &Analyzator::D6;
    }
    void D6b()
    {
        RKL = OPERAND;
        pfunc = &Analyzator::D6;
    }
    void E1a()
    {
        RKL = GOTO;
        pfunc = &Analyzator::E1;
    }
    void E1b()
    {
        RKL = GOSUB;
        pfunc = &Analyzator::E1;
    }
    void E2a()
    {
        RKL = ROWLABEL;
        RSTR = RZN;
        pfunc = &Analyzator::E2;
    }
    void E2b()
    {
        RSTR = RZN;
        pfunc = &Analyzator::E2;
    }
    void E2c()
    {
        RSTR *= 10;
        RSTR += RZN;
        pfunc = &Analyzator::E2;
    }
    void F1a()
    {
        RKL = LET;
        pfunc = &Analyzator::F1;
    }
    void F1b()
    {
        RKL = FOR;
        pfunc = &Analyzator::F1;
    }
    void F2a()
    {
        RI = RZN;
        pfunc = &Analyzator::F2;
    }
    void F3a()
    {
        RI += (RZN) * 26;
        pfunc = &Analyzator::F3;
    }
    void G1a()
    {
        RKL = REM;
        AddLexeme();
        pfunc = &Analyzator::G1;
    }
    void G1b()
    {
        RKL = _ERROR;
        AddLexeme();
        pfunc = &Analyzator::G1;
    }
    void H1a()
    {
        RKL = ATTIT;
        ROT = RZN;
        pfunc = &Analyzator::H1;
    }
    void H1b()
    {
        AddLexeme();
        RKL = ATTIT;
        ROT = RZN;
        pfunc = &Analyzator::H1;
    }
    void H1c()
    {
        AddLexeme();
        RKL = ATTIT;
        ROT = RZN;
        pfunc = &Analyzator::H1;
    }
    void H1f()
    {
        H1b();
        RKL = ATTIT;
        ROT = RZN;
        pfunc = &Analyzator::H1;
    }
    void M1()
    {
        if (ROB == -1)
        {
            G1b();
            return;
        }
        if (RZN == table_alternatives[ROB].letter)
        {
            (this->*(table_alternatives[ROB].pfunc))();
        }
        else
        {
            ROB = table_alternatives[ROB].alternative;
            if (ROB)
            {
                (this->*(table_alternatives[ROB].pfunc))();
            }
            else
                G1b();
        }
    }
    void M2()
    {
        if (RZN == 5)
        {
            D3a();
            return;
        }
        else
        {
            AddLexeme();
            ROB = start_vector[RZN ];
            pfunc = &Analyzator::B1;
        }
    }
    void M3()
    {
        if (RZN == 5)
        {
            pfunc = &Analyzator::D3;
        }
    }
    void exit1()
    {
        RKL = ENDFILE;
        AddLexeme();
    }
    void exit2()
    {
        AddLexeme();
        RKL = ENDFILE;
        AddLexeme();
    }
    void exit3()
    {
        AddLexeme();
        RKL = ENDFILE;
        AddLexeme();
    }
    void exit4()
    {
        AddLexeme();
        RKL = ENDFILE;
        AddLexeme();
    }
    void exit5()
    {
        AddLexeme();
        RKL = ENDFILE;
        AddLexeme();
    }
    void error2()
    {
        RKL = _ERROR;
        AddLexeme();
        RKL = ENDFILE;
        AddLexeme();
    }

};
