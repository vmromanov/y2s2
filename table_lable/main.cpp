#include <windows.h>
#include "strTable.h"
#include "menu.h"

using namespace std;




int main()
{

	Hash a(50,20);
	
    int choice, key;

    SetConsoleOutputCP(1251); // ��� ������ 
    SetConsoleCP(1251); // ��� �����

    do {
        system("pause");
        system("cls");

        std::cout << "\n����:\n";
        std::cout << "1. �������� �������\n";
        std::cout << "2. ������� �������\n";
        std::cout << "3. ���������� �������\n";
        std::cout << "4. �����\n";
        std::cout << "�������� ��������: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "������� ��������: ";
            std::cin >> key;
            a.el_add(key);
            break;
        case 2:
            std::cout << "������� �������� ��� ��������: ";
            std::cin >> key;
            a.el_del(key);
            break;
        case 3:
            a.print();
            break;
        case 4:
            std::cout << "����� �� ���������.\n";
            break;
        default:
            std::cout << "������������ �����. ����������, ���������� �����.\n";

        }
    } while (choice != 4);

	/*a.el_add(100);
	a.el_add(200);
	a.el_add(300);
	a.el_add(500);
	a.el_add(1000);
	a.print();
	a.el_del(300);
	a.print();
	a.el_del(200);
	a.print();
	a.el_add(700);
	a.print();*/

}