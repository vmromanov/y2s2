#include "lexer.h"
int main()
{
    setlocale(LC_ALL, "RUS");
    try {
        Analyzator analyzer;
        analyzer.start("test3.txt"); 
    }
    catch (...) {
        cerr << "������ ��� ���������� �������!\n"
            << "��������� ������� �������� ����� � ����� �������\n";
        return 1;
    }
    return 0;
}