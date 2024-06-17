#include <iostream>
using namespace std;

int move_hanoi(int n)
{
	if (n == 1)
		return 2;
	else
		return move_hanoi(n - 1) * 3 + 2;
}

int main()
{
	int n;
	cin >> n;
	cout << move_hanoi(n);
	return 0;
}