#pragma once

#include <string>
#include "machine.h"

using namespace std;



const unsigned states_amount3 = 5;


class machine3 :public Machine
{
	typedef int(machine3::* fptr)();
	fptr s_table[states_amount3][alfabet_size];

	int one() { return q1; }

	int Zero() { return states::begin; }

	int Fone() { return q2; }

public:

	machine3()
	{
		val = 0;
		s_table[states::begin][zero] = &machine3::Zero;
		s_table[states::begin][One1] = &machine3::one;
		s_table[states::begin][ln] = &machine3::End;

		s_table[q1][zero] = &machine3::Zero;
		s_table[q1][One1] = &machine3::Fone;
		s_table[q1][ln] = &machine3::End;

		s_table[q2][zero] = &machine3::Zero;
		s_table[q2][One1] = &machine3::ERROR;
		s_table[q2][ln] = &machine3::End;
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