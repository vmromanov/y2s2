#include <locale>
#include "asm_code_gen.h"



int main()
{
	setlocale(LC_ALL, "RUS");

	// ����� ����� �� ������
	asm_code_gen g("prg.txt");
	try
	{
		g.code_gen();
	}
	catch (...)
	{
		cout << "������ ��� ���������� �������" << endl << "��������� ������� �������� ����� ��� ������ � ������";
	}
}