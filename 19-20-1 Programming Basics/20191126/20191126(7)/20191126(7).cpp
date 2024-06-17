#include <iostream>
using namespace std;

int main()
{
	int n, m, i, j, temp;
	cin >> n >> m;
	int (*p)[4] = new int[m][4];
	for (i = 0; i < m; i++) {
		for (j = 0; j < 4; j++)
			cin >> p[i][j];
	}
	int (*q)[20][2] = new int[n][20][2];
	for (i = 0; i < n; i++) {
		for (j = 0; j < 20; j++) {
			q[i][j][0] = 0;
			q[i][j][1] = 0;
		}		
	}
	for (i = 0; i < m; i++) {
		if (p[i][3] == 1) {
			q[p[i][0] - 1][p[i][1] - 1][0] += p[i][2];
			q[p[i][0] - 1][p[i][1] - 1][1] = 1;
		}
		else
			q[p[i][0] - 1][p[i][1] - 1][0] += 1200;
	}
	int (*r)[3] = new int[n][3];
	for (i = 0; i < n; i++) {
		r[i][0] = i + 1;
		r[i][1] = 0;
		r[i][2] = 0;
		for (j = 0; j < 20; j++) {
			if (q[i][j][1] == 1) {
				r[i][1] += 1;
				r[i][2] += q[i][j][0];
			}
		}
	}
	for (i = 0; i < n; i++) {
		for (int j = 0; j < n - i - 1; j++)
		{
			if (r[j][1] < r[j + 1][1] || (r[j][1] == r[j + 1][1] && r[j][2] > r[j + 1][2]))
			{
				temp = r[j][0];
				r[j][0] = r[j + 1][0];
				r[j + 1][0] = temp;
				temp = r[j][1];
				r[j][1] = r[j + 1][1];
				r[j + 1][1] = temp;
				temp = r[j][2];
				r[j][2] = r[j + 1][2];
				r[j + 1][2] = temp;
			}
		}
	}
	for (i = 0; i < n; i++)
		cout << r[i][0] << ' ';
	return 0;
}