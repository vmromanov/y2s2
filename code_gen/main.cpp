#include <locale>
#include "sintaxer.h"



int main()
{
	setlocale(LC_ALL, "RUS");
	
	// добав тесты на ошибки
	Syntax_analyzer s;
	try
	{
		s.start("kurlik.txt");
	}
	catch (...)
	{
		cout << "ошибка при выполнении анализа" << endl << "проверьте наличие фходного файла или доступ к онному";
	}
}