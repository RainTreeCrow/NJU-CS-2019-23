#include <iostream>
using namespace std;

struct Board {
	int length, margin;
	bool* column;
	bool* leftDiag;
	bool* rightDiag;
};

int num;

void putQueen(Board b, int row) {
	for (int col = 0; col < b.length; col++) {
		if (b.column[col] && b.leftDiag[row + col] && b.rightDiag[row - col + b.margin]) {
			b.column[col] = false;
			b.leftDiag[row + col] = false;
			b.rightDiag[row - col + b.margin] = false;
			if (row < b.length - 1)
				putQueen(b, row + 1);
			else
				num += 1;
			b.column[col] = true;
			b.leftDiag[row + col] = true;
			b.rightDiag[row - col + b.margin] = true;
		}
	}
}

int main()
{
	num = 0;
	int n, i;
	cin >> n;
	Board b;
	b.length = n;
	b.margin = n - 1;
	b.column = new bool[n];
	b.leftDiag = new bool[n * 2 - 1];
	b.rightDiag = new bool[n * 2 - 1];
	for (i = 0; i < n; i++)
		b.column[i] = true;
	for (i = 0; i < n * 2 - 1; i++) {
		b.leftDiag[i] = true;
		b.rightDiag[i] = true;
	}
	putQueen(b, 0);
	cout << num <<endl;
	return 0;
}