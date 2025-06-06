#pragma once

#include <iostream>
#include <iomanip>

struct TS_el
{
	int label;		//�������� 
	int index_el;	//��������� � ������� ������
	int next;		//���������� �������
};

class Hash
{
	int n_max;	
	int n_os;	//������ �������� �������
	int nts;	//������ ��������� ������� � ������� ������������

	TS_el* t;

	int hashfunc(int key) { return (key % n_os) + 1; }

public:

	friend ostream& operator<<(ostream& os, const Hash& hash);

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

	int Find(int key) // ���������� ����� �������� � ������� �� �����
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

	int TL_inf(int i)
	{
		if (i >= n_max)
			return -1;
		return t[i].index_el;
	}

	int TL_L_inf(int i)
	{
		return t[i].label;
	}

	void el_del(int key)
	{


		int k = hashfunc(key);
		if (t[k].label == -1)
			return;

		if (t[k].label == key && t[k].next == 0) // ������� ������� � �������� ������� � �������� ��� ���������
		{
			t[k].label = -1;
			t[k].index_el = -1;
			return;
		}


		if (t[k].label == key && t[k].next != 0) // ������� ������� � �������� ������� � �������� ���� ���������
		{
			int p = k;
			int sv = t[k].next; // ������ ������ ������� �� � ��� ���
			while (t[t[p].next].next != 0) // x1 x2 x3 x4   p - ������ ��������������(x3)
			{
				p = t[p].next;
			}
			t[k] = t[t[p].next]; // ��������� ���� ������� � ���. �������
			t[k].next = sv;
			t[t[p].next].next = 0;
			t[t[p].next].index_el = -1;
			t[t[p].next].label = -1;
			if (t[0].next == 0) t[0].next = t[p].next;  // ���� �� ������� �� ����� - ������ ������� � �������� ������ ���� � t[0].next
			else
			{// ���� �� ����� ���� ���� ������� ��� �������� - � next �������� ���������� ������ ������ �������� � � t[0].next ������ ������ ��������
				int cpy = t[0].next;
				t[0].next = t[p].next;
				t[t[p].next].next = cpy;
			}
			t[p].next = 0;
			
			return;
		}


		// ���� �������� ���������� �� �������
		while (t[t[k].next].label != key)    // x1 x2....xn-1 xn xn+1   | xn - ����, k - ������ xn-1
			k=t[k].next;

		int cpy = t[k].next; // cpy - ������ xn
		t[k].next = t[cpy].next;   // ����� � xn-1 = xn+1
		t[cpy].label = -1;
		// t[cpy].index_el = -1;
		if (t[0].next == 0) { t[0].next = cpy; t[cpy].next = 0; }// ���� � next � t[0] ����� �� ���� ���, ��������� ������ ���������� �������� � t[0].next �� ������� ����
		else
		{     // ���� ���� => � t[0].next �������� ������ ���������� �������� cpy, � � next � ���������� �������� �������� ������ �������� ���� 
			int cpy1 = t[0].next; //cpy1 - ������ ���������� ���� �� ������ ��������
			t[0].next = cpy;
			t[cpy].next = cpy1;
		}
		return;
	}

	int el_add(int key,int ind)
	{
		int k = hashfunc(key);
		if (t[k].label == -1)
		{
			t[k].label = key;
			t[k].index_el = ind;
			return k;
		}

		int p = k;
		while (t[p].next != 0) // ���� �� ����� next
			p = t[p].next; // p - ������ ����������

		if (t[0].next == 0 ) // ���� ��� ������ ����� �� ������ nts
		{
			t[p].next = nts;
			t[nts].label = key;
			t[nts].index_el = ind;
			nts++;
			return nts-1;
		}

		if (t[0].next != 0)
		{
			t[p].next = t[0].next;
			int sv = t[0].next;  // sv - ������ ���������� ����������
			t[0].next = t[sv].next; // �� "������� �����" �������� ������ �������������� ����������
			t[sv].label = key;
			t[sv].index_el = ind;
			t[sv].next = 0;
			return sv;
		}

	}

	void print(ofstream& fout) {
		for (int i = 1; i < nts; ++i) {
			if (t[i].label != -1) {
				fout << i << " " << t[i].label << endl;
			}
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









