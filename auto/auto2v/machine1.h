#pragma once

#include <string>
#include "machine.h"

using namespace std;

enum states1{One=3,even_one,even_zero, not_even_zero};

const unsigned states_amount = 7;

class machine1 :public Machine
{
	typedef int(machine1::* fptr)();
	fptr s_table[states_amount][alfabet_size];

	int one() { return states1::One; }

	int Eone() { return states1::even_one; }

	int Ezero() { return states1::even_zero; }

	int NEzero() { return states1::not_even_zero; }

public:
	machine1()
	{
		val = 0;
		s_table[states::begin][zero] = &machine1::NEzero;
		s_table[states::begin][One1] = &machine1::one;
		s_table[states::begin][ln] = &machine1::ERROR;

		s_table[One][zero] = &machine1::ERROR;
		s_table[One][One1] = &machine1::Eone;
		s_table[One][ln] = &machine1::ERROR;

		s_table[even_one][zero] = &machine1::NEzero;
		s_table[even_one][One1] = &machine1::one;
		s_table[even_one][ln] = &machine1::ERROR;

		s_table[not_even_zero][zero] = &machine1::Ezero;
		s_table[not_even_zero][One1] = &machine1::ERROR;
		s_table[not_even_zero][ln] = &machine1::End;

		s_table[even_zero][zero] = &machine1::NEzero;
		s_table[even_zero][One1] = &machine1::ERROR;
		s_table[even_zero][ln] = &machine1::ERROR;
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