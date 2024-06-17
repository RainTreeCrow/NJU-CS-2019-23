#include <iostream>
using namespace std;

int main()
{
	int m, n, i, fm, fn, fmn, cmn;
	cin >> m >> n;
	fm = 1, fn = 1, fmn = 1;
	for (i = 1; i <= m; i++)
		fm = fm * i;
	if (n != 0)
		for (i = 1; i <= n; i++)
			fn = fn * i;
	for (i = 1; i <= m - n; i++)
		fmn = fmn * i;
	cmn = fm / (fn * fmn);
	cout << cmn;
	return 0;
}