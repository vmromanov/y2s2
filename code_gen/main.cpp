#include <locale>
#include "asm_code_gen.h"



int main()
{
	setlocale(LC_ALL, "RUS");

	// добав тесты на ошибки
	asm_code_gen g("prg.txt");
	try
	{
		g.code_gen();
	}
	catch (...)
	{
		cout << "ошибка при выполнении анализа" << endl << "проверьте наличие фходного файла или доступ к онному";
	}
}