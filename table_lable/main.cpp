#include "strTable.h"






int main()
{
	Hash a(150,50);

	a.el_add(100);
	a.el_add(200);
	a.el_add(300);
	a.el_add(500);
	a.print();
	a.el_del(300);
	a.print();
	a.el_add(700);
	a.print();

}