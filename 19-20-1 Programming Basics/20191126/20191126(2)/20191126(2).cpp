#include <iostream>
#include <cstring>
using namespace std;

int* process(string x)
{
	int l = x.length();
	int* px = new int[x.length()];
	for (int i = 0; i < l; i++)
		px[l - i - 1] = x[i] - 48;
	return px;
}

int main()
{
	string a, b;
	cin >> a >> b;
	int al = a.length(), bl = b.length();
	if (a == "0" || b == "0")
		cout << "0";
	else {
		int* A = process(a);
		int* B = process(b);
		int* result = new int[al + bl];
		for (int i = 0; i < al + bl; i++)
			result[i] = 0;
		for (int i = 0; i < al; i++) {
			for (int j = 0; j < bl; j++)
				result[i + j] += A[i] * B[j];
		}
		for (int i = 0; i < al + bl - 1; i++) {
			if (result[i] > 9) {
				result[i + 1] += result[i] / 10, result[i] %= 10;
			}
		}
		bool flag = false;
		for (int i = al + bl - 1; i >= 0; i--)
			if (result[i] != 0 || flag == true) {
				cout << result[i];
				flag = true;
			}
	}
	return 0;
}