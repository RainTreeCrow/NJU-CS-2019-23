#include <iostream>
using namespace std;

int main()
{
	int n, i, j, temp0, temp1;
	cin >> n;
	int(*interval)[3] = new int[n][3];
	for (i = 0; i < n; i++) {
		cin >> interval[i][0] >> interval[i][1];
		interval[i][2] = 1;
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < n - i - 1; j++) {
			if (interval[j][0] > interval[j + 1][0]) {
				temp0 = interval[j][0];
				temp1 = interval[j][1];
				interval[j][0] = interval[j + 1][0];
				interval[j][1] = interval[j + 1][1];
				interval[j + 1][0] = temp0;
				interval[j + 1][1] = temp1;
			}
		}
	}
	for (i = 0; i < n; i++) {
		if (interval[i][2] == 1) {
			for (j = i + 1; j < n; j++) {
				if (interval[j][2] == 1 && interval[i][1] >= interval[j][0]) {
					interval[i][1] = interval[j][1];
					interval[j][2] = 0;
				}
			}
		}
	}
	for (i = 0; i < n; i++) {
		if (interval[i][2] == 1)
			cout << interval[i][0] << ' ' << interval[i][1] << endl;
	}
}