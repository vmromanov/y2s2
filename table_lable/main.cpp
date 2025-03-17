#include <windows.h>
#include "strTable.h"

using namespace std;

int main()
{
    // os = 50 size = 150


	Hash* a;
    int OS, SIZE;
    int choice, key;
    int srch;
    SetConsoleOutputCP(1251); // ��� ������ 
    SetConsoleCP(1251); // ��� �����

    std::cout << "������� ������ �������� ������� �������: ";
    std::cin >> OS;
    std::cout << "������� ������ ���� �������: ";
    std::cin >> SIZE;

    a = new Hash(SIZE, OS);


    do {
        system("pause");
        system("cls");

        std::cout << "\n����:\n";
        std::cout << "1. �������� �������\n";
        std::cout << "2. ������� �������\n";
        std::cout << "3. ���������� �������\n";
        std::cout << "4. ����� �������\n";
        std::cout << "5. �����\n";
        std::cout << "�������� ��������: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "������� ��������: ";
            std::cin >> key;
            a->el_add(key);
            break;
        case 2:
            std::cout << "������� �������� ��� ��������: ";
            std::cin >> key;
            a->el_del(key);
            break;
        case 3:
            a->print();
            break;
        case 4:
            std::cout << "������� �������� ��� ������: ";
            std::cin >> key;

            srch = a->Find(key);

            if (srch == -1)
            {
                cout << "������� �� ������";
            }
            else
            {
                cout << "������� ��������� � ������� �� ������� " << srch << endl;
            }
            break;
        case 5:
            std::cout << "����� �� ���������.\n";
            break;
        default:
            std::cout << "������������ �����. ����������, ���������� �����.\n";

        }
    } while (choice != 5);

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