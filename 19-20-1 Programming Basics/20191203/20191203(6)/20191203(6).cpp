#include <iostream>
#include <string>
using namespace std;

int main()
{
	int n;
	string s;
	cin >> n;
	cin >> s;
	int m = s.length() / n;
	char (*c)[20] = new char[m][20];
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < 20; j++)
			c[i][j] = '0';
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (i % 2 == 0) {
				c[i][j] = s[i * n + j];
			}
			else {
				c[i][n - j - 1] = s[i * n + j];
			}
		}
	}
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < m; i++)
			cout << c[i][j];
	}
	return 0;
}