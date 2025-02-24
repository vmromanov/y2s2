#pragma once

#include <iostream>
#include <vector>
#include <map>
using namespace std;

struct player
{
	string name;
	unsigned N;
};

void out(vector<player> a)
{
	cout << " " << a[0].name;
	for (int i = 1; i < a.size(); i++)
		cout << "," << a[i].name;
	cout << endl;
}

void sch(vector<player>& a,unsigned k)
{
	if (a.empty())
	{
		string err = "no players";
		throw err;
	}
	if (a.size() == 1)
	{
		cout << "only one player";
		return;
	}
	if (k == 1)
	{
		vector<player> deleted = a;
		deleted.pop_back();
		cout << "deleting order: ";
		out(deleted);
		string name_left = a[a.size() - 1].name;
		cout << "left: " << name_left << "his number: "<< a[a.size() - 1].N;
	}

	vector<player> deleted;

	int i = 1;
	int d = 0;
	int size = a.size();
	while (size != 1)
	{
		if (d == size) d = 0;
		if (i == k)
		{
			deleted.push_back(a[d]);
			cout << endl<< a[d].name<<endl; //кого выкидываем
			for (int u =d; u < size - 1; u++)
			{
				a[u] = a[u + 1];
			}
			
			a.pop_back();
			
			cout << endl;
			for (player el : a)
				cout << " " << el.name;
			cout  << " " << d<< endl;
			
			size--;

			i = 1;
			continue;
		}
		i++;
		d++;
	}

	cout << "deleting order: ";
	out(deleted);
	cout << "left: " << a[0].name << "  his number: " << a[0].N;
}





