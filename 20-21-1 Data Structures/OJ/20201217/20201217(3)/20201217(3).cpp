#include <iostream>
using namespace std;

bool isValid(int r, int*& board, bool**& water) {
	if (water[r][board[r]])
		return false;
	for (int i = 0; i < r; i++) {
		if (board[r] == board[i] || abs(r - i) == abs(board[r] - board[i]))
			return false;
	}
	return true;
}

void TraceBack(int r, int n, int*& board, bool**& water, int& methods) {
	if (r >= n) {
		methods++;
	}
	else {
		for (int i = 0; i < n; i++) {
			board[r] = i;
			if (isValid(r, board, water))
				TraceBack(r + 1, n, board, water, methods);
		}
	}
}

int main()
{
    int m, n;
    cin >> n >> m;
	int* board = new int[n];
    bool** water = new bool* [n];
    for (int i = 0; i < n; i++) {
        water[i] = new bool[n];
        for (int j = 0; j < n; j++)
            water[i][j] = false;
    }
    int x, y;
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        water[x - 1][y - 1] = true;
    }
	int methods = 0;
	TraceBack(0, n, board, water, methods);
	cout << methods;
	return 0;
}