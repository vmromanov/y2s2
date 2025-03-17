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
    SetConsoleOutputCP(1251); // Для вывода 
    SetConsoleCP(1251); // Для ввода

    std::cout << "введите размер основной области таблицы: ";
    std::cin >> OS;
    std::cout << "введите размер всей таблицы: ";
    std::cin >> SIZE;

    a = new Hash(SIZE, OS);


    do {
        system("pause");
        system("cls");

        std::cout << "\nМеню:\n";
        std::cout << "1. Добавить элемент\n";
        std::cout << "2. Удалить элемент\n";
        std::cout << "3. Напечатать таблицу\n";
        std::cout << "4. найти элемент\n";
        std::cout << "5. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Введите значение: ";
            std::cin >> key;
            a->el_add(key);
            break;
        case 2:
            std::cout << "Введите значение для удаления: ";
            std::cin >> key;
            a->el_del(key);
            break;
        case 3:
            a->print();
            break;
        case 4:
            std::cout << "введите значение для поиска: ";
            std::cin >> key;

            srch = a->Find(key);

            if (srch == -1)
            {
                cout << "элемент не найден";
            }
            else
            {
                cout << "элемент находится в таблице на позиции " << srch << endl;
            }
            break;
        case 5:
            std::cout << "Выход из программы.\n";
            break;
        default:
            std::cout << "Некорректный выбор. Пожалуйста, попробуйте снова.\n";

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