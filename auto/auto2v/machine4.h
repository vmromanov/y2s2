#pragma once
#include <string>
#include "machine.h"

using namespace std;



const unsigned states_amount4 = 5;

class machine4 :public Machine
{
	typedef int(machine4::* fptr)();
	fptr s_table[states_amount3][alfabet_size];

	int one() { return q1; }

	int Zero() { return states::begin; }

	int Two() { return q2; }

public:

	machine4()
	{
		val = 0;
		s_table[states::begin][zero] = &machine4::one;
		s_table[states::begin][One1] = &machine4::one;
		s_table[states::begin][ln] = &machine4::End;

		s_table[q1][zero] = &machine4::Two;
		s_table[q1][One1] = &machine4::Two;
		s_table[q1][ln] = &machine4::End;

		s_table[q2][zero] = &machine4::ERROR;
		s_table[q2][One1] = &machine4::Zero;
		s_table[q2][ln] = &machine4::End;
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