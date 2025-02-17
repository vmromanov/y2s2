#pragma once

#include <string>
#include "machine.h"

using namespace std;

enum states2 { q1 = 3,  q2};

const unsigned states_amount2 = 5;

class machine2 :public Machine
{
	typedef int(machine2::* fptr)();
	fptr s_table[states_amount2][alfabet_size];

	int one() { return states2::q1; }

	int Zero() { return states::begin; }

	int Fone() { return states2::q2; }

public:

	machine2()
	{
		val = 0;
		s_table[states::begin][zero] = &machine2::Zero;
		s_table[states::begin][One1] = &machine2::one;
		s_table[states::begin][ln] = &machine2::End;

		s_table[q1][zero] = &machine2::Fone;
		s_table[q1][One1] = &machine2::one;
		s_table[q1][ln] = &machine2::End;

		s_table[q2][zero] = &machine2::one;
		s_table[q2][One1] = &machine2::ERROR;
		s_table[q2][ln] = & machine2::End;
	}

	bool parse(const string strk)
	{
		int cur_state = states::begin;
		auto it = strk.begin();

		while (cur_state != states::end && cur_state != error)
		{
			if (it == strk.end())val = '\n';
			else val = *(it++);
			int t = transliterator(val);
			if (t == -1) cur_state = states::error;
			else
				cur_state = (this->*s_table[cur_state][t])();
		}
		if (cur_state == states::error)return false;
		else return true;
	}

};
