#include "lexer.h"
#include <Windows.h>
int main()
{
    setlocale(LC_ALL, "RUS");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    try {
        Analyzator analyzer;
        analyzer.start("test1.txt"); 
    }
    catch (...) {
        cerr << "������ ��� ���������� �������!\n"
            << "��������� ������� �������� ����� � ����� �������\n";
        return 1;
    }
    return 0;
}