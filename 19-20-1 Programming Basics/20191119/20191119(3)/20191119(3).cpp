#include <iostream>
#include <string>
using namespace std;

int main()
{
	int i, j, k, num, yes, factor[1000];
	for (i = 0; i < 1000; i++)
		factor[i] = 0;
	string str;
	getline(cin, str);
	num = str.size();
	factor[0] = 1;
	j = 1;
	for (i = 2; i <= num / 2; i++)
	{
		if (num % i == 0)
		{
			factor[j] = i;
			j += 1;
		}
	}
	yes = j;
	for (i = 0; i < j; i++)
	{
		for (k = 0; k < factor[i]; k++)
		{
			if (str[k] != str[k + factor[i]])
			{
				yes -= 1;
				break;
			}
		}
	}
	if (yes > 0)
		cout << "YES";
	else
		cout << "NO";
	return 0;
}