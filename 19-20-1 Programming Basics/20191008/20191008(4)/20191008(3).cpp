#include <iostream>
using namespace std;

int main()
{
	int i = 1;
	int a = 0, b = 0, c = 0, d = 0;
	while (i <= 10)
	{
		char x = getchar();
		if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
		{
			a++;
		}
		else if (x >= '0' && x <= '9')
		{
			b++;
		}
		else if (x == ' ')
		{
			c++;
		}
		else
		{
			d++;
		}
		i = i + 1;
	}
	cout << a << "\n" << b << "\n" << c << "\n" << d << endl;
	return 0;
}