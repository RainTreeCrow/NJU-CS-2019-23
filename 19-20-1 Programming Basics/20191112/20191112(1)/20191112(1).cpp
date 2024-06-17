#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int n, i, j, k, m, x = 0;
	double cj, c = 0;
	const double ZERO = 1.0e-6;
	cin >> n;
	double* a = new double[n];
	int b[100][2];
	for (i = 0; i < 100; i++) {
		b[i][0] = 0;
		b[i][1] = 0;
	}
	for (i = 0; i < n; i++) {
		cin >> a[i];
		c += a[i];
	}
	for (j = 0; j < n - 1; j++) {
		cj = a[j];
		for (k = j + 1; k < n; k++) {
			if (abs(cj - c / 2) <= ZERO) {
				b[x][0] = j;
				b[x][1] = k;
				x += 1;
				break;
			}
			cj += a[k];
		}
	}
	m = x ;
	cout << m * (m - 1) / 2;
	cout << '\n';
	for (i = 0; i < x - 1; i++) {
		for (j = i + 1; j < x; j++)
			cout << b[i][0] << ' '<< b[j][0] << ' '<< b[i][1] << ' '<< b[j][1] << ' ';
	}
}