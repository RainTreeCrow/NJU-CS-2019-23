#include <iostream>
#include <string>
using namespace std;

void f(string s)
{
	int i, num = 0;
	for (i = 0; i < s.size(); i++)
	{
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] -= 32;
		if (s[i] != ' ')
			num += 1;
	}
	cout << s << num;
}

int main()
{
	string s;
	getline(cin, s);
	f(s);
	return 0;
}