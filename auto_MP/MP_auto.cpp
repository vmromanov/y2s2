#include <stack>
#include <string>
#include <iostream>
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
					break;
				case '0':
					st.pop();
					break;
				default:
					return false;
				}
			else
				return false;
			break;
		case 'D':
			if (i != sz)
				switch (str[i])
				{
				case '1':
					st.push('1');
					i++;
					break;
				default:
					return false;
				}
			else
				return true;
			break;
		case '1':
			if (i != sz)
				switch (str[i])
				{
				case '1':
					st.pop();
					i++;
					break;
				case '0':
					st.pop();
					i++;
					break;
				default:
					return false;
				}
			else
				return false;
			break;
		case 'k':
			if (i != sz)
				switch (str[i])
				{
				case '1':
					st.pop();
					st.pop();
					i++;
					break;
				default:
					return false;
				}
			else 
				return false;
			break;
		case 'j':
			if (i != sz)
				switch (str[i])
				{
				case '1':
					st.push('k');
					i++;
					break;
				default:
					return false;

				}
			else 
				return false;
			break;
		default:
			return false;
			break;
		}
	}



}

int main()
{
	string s;
	s = "11111100000000000011111111";
	cout << is_allowed(s);
}



