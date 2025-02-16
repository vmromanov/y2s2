#include <string>
#include <iostream>

#include "Auto1.h"
#include "Auto2.h"
#include "Auto3.h"
#include "Auto4.h"
using namespace  std;

int main()
{
	auto1 b;
	b.start("1111000");

	cout << "\nsecond:\n";

	auto2 c;
	c.start("00100100");

	cout << "\nthird:\n";

	auto3 d;
	d.start("1101011");

	cout << "\nfourth\n";

	auto4 e;
	e.start("000001011111");

	return 0;
}
