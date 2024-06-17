#include <iostream>
using namespace std;

int main()
{
	string s;
	cin >> s;
	int count = 0;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == '(')
			count += 1;
		else if (s[i] == ')')
		{
			count -= 1;
			if (count < 0)
				break;
		}
	}
	if (count == 0)
		cout << "correct";
	else
		cout << "false";
	return 0;
}