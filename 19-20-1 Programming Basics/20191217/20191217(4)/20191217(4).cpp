#include <iostream>
using namespace std;

void p(int f[20][20], int i, int n, bool *u)
{
	u[i] = false;
	for (int j = 0; j < n; j++) {
		if (f[i][j] == 1 && u[j])
			p(f, j, n, u);
	}
}

int main()
{
	int n, i, j, c = 0;
	cin >> n;
	int friends[20][20];
	bool* uncounted = new bool[n];
	for (i = 0; i < n; i++) {
		uncounted[i] = true;
		for (j = 0; j < n; j++) {
			cin >> friends[i][j];
		}
	}
	for (i = 0; i < n; i++) {
		if (uncounted[i]) {
			p(friends, i, n, uncounted);
			c += 1;
		}
	}
	cout << c << endl;
	return 0;
}