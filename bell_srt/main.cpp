#include <vector>
#include <iostream>
using namespace std;

void bell_sort(vector<double>& arr)
{
	if (arr.size() == 0||arr.size()==1) return;
	
	double mi = numeric_limits<double>::max();
	double src = mi;
	int sz = arr.size();
	bool f = 0; // 0 - всавка слева, 1 - справа
	double* a = new double[sz];
	
	int li = 0;	// li - сколько уже вставили слева
	int ri = 0;	// ri - сколько уже вставили справа

	for (double el : arr)
		if (el < mi)mi = el;
	ri++;

		a[sz-1] = mi;

	while ((ri+li)<sz)
	{
		for (double el : arr )
			if (el < src&&el>mi)src = el;

		if (f == 0)
		{
			a[li] = src;
			f = 1;
			li++;
		}
		else
		{
			a[sz-ri-1] = src;
			f = 0;
			ri++;
		}
		mi = src;
		src = numeric_limits<double>::max();
	}


	vector<double> u;
	for (int i = 0; i < sz; i++)
		u.push_back(a[i]);
	arr = u;

	delete[] a;
	return;
}

void bell_out(vector<double> v)
{
	int sz = v.size();
	int tp = sz / 2;
	int itp = 1;
	int k = 0;
	double lx, rx;
	if (v.size() % 2 != 0)
	{
		while (tp != -1)
		{
			for (int i = 0; i < tp;i++)
				cout << '\t';
			
			lx = v[sz / 2 - k];
			rx = v[sz / 2 + k];
			if (lx == rx)
			{
				cout << lx;
			}
			else
			{
				cout << lx;
				for (int i = 0; i < itp-1; i++)
					cout << '\t';
				cout << rx;
			}
			for (int i = 0; i < tp; i++)
				cout << '\t';
			tp--;
			itp == 0 ? itp++ : itp += 2;
			k++;
			cout << endl;
		}

	}
	else
	{
		tp--;
		itp++;
		while (tp != -1)
		{
			lx = v[sz / 2 - k - 1];
			rx = v[sz / 2 + k];


			for (int i = 0; i < tp; i++)
				cout << '\t';
			cout << lx;
			for (int i = 0; i < itp; i++)
				cout << '\t';
			cout << rx;
			for (int i = 0; i < tp; i++)
				cout << '\t';
			itp += 2;
			tp--;
			k++;
			cout << endl;
		}
	}
}

int main()
{
	vector<double> a = { 7,8,5,3,4,1 };
	bell_sort(a);
	bell_out(a);
	return 0;
}