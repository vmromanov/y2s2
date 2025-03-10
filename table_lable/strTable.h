#pragma once

struct TS_el
{
	int label; 
	int index_el;	//��������� � ������� ������
	int next;		//���������� �������
};


class Hash
{
	int n_max;
	int n_os;	//������ �������� �������
	int nts;	//������ ��������� ������� � ������� ������������
	TS_el* t;
	int hashfunc(int key) { return (key % 100) + 1; }


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
			t[i].label = other.t[i].label;
			t[i].index_el = other.t[i].index_el;
			t[i].next = other.t[i].next;
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

	// ����� ����, ���� ����

	void el_del(int key)
	{
		int k = hashfunc(key);
		if (t[k].label == key && t[k].next == 0)
		{
			t[k].label = -1;
			t[k].index_el = -1;
			return;
		}
		if (t[k].label == key && t[k].next != 0)
		{
			int p = t[k].next;
			while (t[t[p].next].next != 0) // x1 x2 x3 x4   p - ������ ��������������(x3)
			{
				p = t[p].next;
			}

		}
	}

	void el_add(int key)
	{
		int k = hashfunc(key);
		if (t[k].label == -1)
		{
			t[k].label = key;
			// t[k].index_el=
			return;
		}

		if (t[k].next == 0)
		{
			t[k].next = nts;
			t[nts].label = key;
			// t[nts].index_el =
			nts++;
			return;
		}

		int p = t[k].next;
		while (t[p].next != 0) // ���� �� ����� next
			p = t[p].next;


	}






};









