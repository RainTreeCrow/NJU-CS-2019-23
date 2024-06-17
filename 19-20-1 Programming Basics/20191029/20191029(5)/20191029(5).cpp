#include <iostream>
using namespace std;

void delete_repeated(string s)
{
	int i, j, k, l;
	l = s.size();
	for (i = 0; i < l; i++)
	{
		for (j = i + 1; j < l; j++)
		{
			if (s[j] == s[i])
			{
				for (k = j; k < l; k++)
				{
					s[k] = s[k + 1];
					s[l] = '0';
				}
				l -= 1;
				j -= 1;
			}
		}
	}
	for (i = 0; i < l; i++)
	{
		if (s[i] != '0')
			cout << s[i];
	}
}

int main()
{
	string s;
	cin >> s;
	delete_repeated(s);
	return 0;
}