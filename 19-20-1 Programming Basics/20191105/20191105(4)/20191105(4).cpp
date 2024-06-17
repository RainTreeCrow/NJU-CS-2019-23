#include <iostream>
using namespace std;

void move(int n, char start, char middle, char end)
{
	if (n == 1)
		cout << "Move disk " << n << " from " << start << " to " << end << '\n';
	else
	{
		move(n - 1, start, end, middle);
		cout << "Move disk " << n << " from " << start << " to " << end << '\n';
		move(n - 1, middle, start, end);
	}
}

int main()
{
	int n;
	char start = 'A', middle = 'B', end = 'C';
	cin >> n;
	move(n, start, middle, end);
	return 0;
}