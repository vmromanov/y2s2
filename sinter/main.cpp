#include <locale>
#include "sintaxer.h"



int main()
{
	setlocale(LC_ALL, "RUS");


	Syntax_analyzer s;
	try
	{
		s.start("test1.txt");
	}
	catch (...)
	{
		cout << "ошибка при выполнении анализа" << endl << "проверьте наличие фходного файла или доступ к онному";
	}
}