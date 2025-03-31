#pragma once

#include <iostream>
#include <iomanip>

struct TS_el
{
	int label;		//значение 
	int index_el;	//положение в таблице лексем
	int next;		//разрешение колизий
};

class Hash
{
	int n_max;	
	int n_os;	//размер основной области
	int nts;	//первая свободная область в области переполнения

	TS_el* t;

	int hashfunc(int key) { return (key % n_os) + 1; }

public:

	Hash(int n1 = 1000, int os = 200)
	{
		n_max = n1;
		n_os = os;
		nts = os + 1;

		t = new TS_el[n_max];

		for (int i = 0; i < n_max; i++)
		{
			t[i].label = t[i].index_el = -1;
			t[i].next = 0;
		}
	}

	Hash(const Hash& other)
	{
		n_max = other.n_max;
		n_os = other.n_os;
		nts = other.nts;;
		t = new TS_el[n_max];

		for (int i = 0; i < n_max; i++)
		{
			t = other.t;
		}
	}

	Hash(Hash& other)
	{
		n_max = other.n_max;
		n_os = other.n_os;
		nts = other.nts;;
		t = new TS_el[n_max];

		for (int i = 0; i < n_max; i++)
		{
			t = other.t;
		}
	}

	~Hash()
	{
		delete[] t;
	}

	int Find(int key) // возвращяет номер элемента в таблице по ключу
	{
		int i = hashfunc(key);

		while (t[i].label != key)
		{
			if (t[i].next != 0)
				i = t[i].next;
			else
				return -1;
		}
		return i;
	}

	// добав элем, удал элем

	void el_del(int key)
	{


		int k = hashfunc(key);
		if (t[k].label == key && t[k].next == 0) // удаляем элемент в основной области у которого нет следующих
		{
			t[k].label = -1;
			t[k].index_el = -1;
			return;
		}


		if (t[k].label == key && t[k].next != 0) // удаляем элемент в основной области у которого есть следующие
		{
			int p = k;
			int sv = t[k].next; // индекс начала цепочки не в осн обл
			while (t[t[p].next].next != 0) // x1 x2 x3 x4   p - индекс предпоследнего(x3)
			{
				p = t[p].next;
			}
			t[k] = t[t[p].next]; // последний элем цепочки в осн. область
			t[k].next = sv;
			t[t[p].next].next = 0;
			t[t[p].next].index_el = -1;
			t[t[p].next].label = -1;
			if (t[0].next == 0) t[0].next = t[p].next;  // если не удаляли до этого - просто удаляем и помещяем индекс окна в t[0].next
			else
			{// если до этого были окна которые еще остались - в next прошлого окнаставим индекс нашего элемента а в t[0].next индекс нашего элемента
				int cpy = t[0].next;
				t[0].next = t[p].next;
				t[t[p].next].next = cpy;
			}
			t[p].next = 0;
			
			return;
		}


		// пока значение следующего не совпадёт
		while (t[t[k].next].label != key)    // x1 x2....xn-1 xn xn+1   | xn - ищим, k - индекс xn-1
			k=t[k].next;

		int cpy = t[k].next; // cpy - индекс xn
		t[k].next = t[cpy].next;   // некст у xn-1 = xn+1
		t[cpy].label = -1;
		// t[cpy].index_el = -1;
		if (t[0].next == 0) { t[0].next = cpy; t[cpy].next = 0; }// если в next у t[0] пусто то окон нет, добавляем индекс удаленного элемента в t[0].next тк создали окно
		else
		{     // окна были => в t[0].next помещяем индекс удаляемого элемента cpy, а в next у удаляемого элемента помещяем индекс прошлого окна 
			int cpy1 = t[0].next; //cpy1 - индекс последнего удал до нашего удаления
			t[0].next = cpy;
			t[cpy].next = cpy1;
		}
		return;
	}

	void el_add(int key)  // переделать чтоб оно возвращяло куда вставило
	{
		int k = hashfunc(key);
		if (t[k].label == -1)
		{
			t[k].label = key;
			// t[k].index_el=
			return;
		}

		int p = k;
		while (t[p].next != 0) // идем до конца next
			p = t[p].next; // p - индекс последнего

		

		if (t[0].next == 0 ) // окон нет просто добав по адресу nts
		{
			t[p].next = nts;
			t[nts].label = key;
			// t[nts].index_el =
			nts++;
			return;
		}

		if (t[0].next != 0)
		{
			t[p].next = t[0].next;
			int sv = t[0].next;  // sv - индекс последнего удаленного
			t[0].next = t[sv].next; // на "вершину стека" помещяем индекс предпоследнего удаленного
			t[sv].label = key;
			//t[sv].index_el = 
			t[sv].next = 0;
			return;
		}

	}

	void print()
	{
		std::cout << std::setw(7) << 0 << "|"
			<< std::setw(10) << t[0].label << "|"
			<< std::setw(10) << t[0].index_el << "|"
			<< std::setw(10) << t[0].next << "|" << std::endl;
		for (int i = 1; i < n_max; i++)
		{
			if (t[i].label!=-1)
			std::cout << std::setw(7) << i << "|"
				<< std::setw(10) << t[i].label << "|"
				<< std::setw(10) << t[i].index_el << "|"
				<< std::setw(10) << t[i].next << "|"<<std::endl ;
		}
		std::cout << std::endl;
	}




};









