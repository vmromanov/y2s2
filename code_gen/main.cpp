#include <locale>
#include "sintaxer.h"



int main()
{
	setlocale(LC_ALL, "RUS");
	
	// ����� ����� �� ������
	Syntax_analyzer s;
	try
	{
		s.start("kurlik.txt");
	}
	catch (...)
	{
		cout << "������ ��� ���������� �������" << endl << "��������� ������� �������� ����� ��� ������ � ������";
	}
}