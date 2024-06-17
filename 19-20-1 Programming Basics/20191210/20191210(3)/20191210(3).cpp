#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	int n, i, j, temp;
	cin >> n;
	int* nums = new int[n];
	for (i = 0; i < n; i++)
		cin >> nums[i];
	for (i = 0; i < n; i++) {
		for (j = 0; j < n - i - 1; j++) {
			if (nums[j] < nums[j + 1]) {
				temp = nums[j];
				nums[j] = nums[j + 1];
				nums[j + 1] = temp;
			}
		}
	}
	if (n % 2 != 0)
		cout << nums[n / 2];
	else {
		float a = nums[n / 2], b = nums[n / 2 - 1];
		float num = (a + b) / 2.0;
		cout << setiosflags(ios::fixed) << setprecision(2);
		cout << setw(2) << num;
	}
	return 0;
}