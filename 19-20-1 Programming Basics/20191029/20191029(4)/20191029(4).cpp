#include <iostream>
#include <string>
using namespace std;

void f(string s, string x)
{
	int i, start = 0, times = 0;
	for (i = 0; i < s.size(); i++)
	{
		if (s[i] == x[0])
		{
			start = i + 1;
			break;
		}
	}
	for (i = 0; i < s.size(); i++)
	{
		if (s[i] == x[0])
			times += 1;
	}
	cout << start << '\n' << times;
}

int main()
{
	string s, string x;
	cin >> s >> x;
	f(s, x);
	return 0;
}