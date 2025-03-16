#include <windows.h>
#include "strTable.h"
#include "menu.h"

using namespace std;




int main()
{

	Hash a(50,20);
	
    int choice, key;

    SetConsoleOutputCP(1251); // Для вывода 
    SetConsoleCP(1251); // Для ввода

    do {
        system("pause");
        system("cls");

        std::cout << "\nМеню:\n";
        std::cout << "1. Добавить элемент\n";
        std::cout << "2. Удалить элемент\n";
        std::cout << "3. Напечатать таблицу\n";
        std::cout << "4. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Введите значение: ";
            std::cin >> key;
            a.el_add(key);
            break;
        case 2:
            std::cout << "Введите значение для удаления: ";
            std::cin >> key;
            a.el_del(key);
            break;
        case 3:
            a.print();
            break;
        case 4:
            std::cout << "Выход из программы.\n";
            break;
        default:
            std::cout << "Некорректный выбор. Пожалуйста, попробуйте снова.\n";

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