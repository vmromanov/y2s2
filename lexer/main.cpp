#include "lexer.h"
int main()
{
    setlocale(LC_ALL, "RUS");
    try {
        Analyzator analyzer;
        analyzer.start("test3.txt"); 
    }
    catch (...) {
        cerr << "Ошибка при выполнении анализа!\n"
            << "Проверьте наличие входного файла и права доступа\n";
        return 1;
    }
    return 0;
}