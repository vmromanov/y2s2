#include <stack>
#include <string>

using namespace std;

void Replace_st(stack<char> *stack,string s)
	{
	stack->pop();
	for (int i = 0; i < s.size(); i++)
		stack->push(s[i]);
	}

bool is_allowed(string str)
{
	stack<char> st;
	char ch;

	st.push('D');
	st.push('j');
	st.push('x');

	int sz = str.size();
	for (int i = 0; i <= sz;) // i==sz => str[i]==eof
	{
		ch = st.top();
		switch (ch)
		{
		case 'x':
			if (i != sz)
				switch (str[i])
				{
				case '1':
					Replace_st(&st, "11x");
					i++;
				case '0':
					st.pop();
				}
			else
				return false;
		case 'D':
			if (i != sz)
				switch (str[i])
				{
				case '1':
					st.push('1');
					i++;
				case '0':
					return false;
				}
			else return true;

		}
	}



}





