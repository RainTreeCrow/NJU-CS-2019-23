#include <iostream>
using namespace std;

int Path(int n)

{
	if (n == 1)
		return 1;
	else if (n == 2)
		return 1;
	else
	{
		if (n % 2 == 0)
			return Path(n - 1) + Path(n - 2) + Path(n - 3);
		else
			return Path(n - 1) + Path(n - 2);
	}
}

int main()
{
	int n;
	cin >> n;
	cout << Path(n);
	return 0;
}