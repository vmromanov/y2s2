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
        cerr << "Ошибка при выполнении анализа!\n"
            << "Проверьте наличие входного файла и права доступа\n";
        return 1;
    }
    return 0;
}