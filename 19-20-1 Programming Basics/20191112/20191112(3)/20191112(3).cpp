#include <iostream>
using namespace std;

int main()
{
	int length, target, i, num;
	cin >> length;
	int *nums = new int[length];
	for (i = 0; i < length; i++)
		cin >> nums[i];
	cin >> target;
	num = 0;
	for (i = 0; i < length; i++)
	{
		if (nums[i] < target)
			num += 1;
	}
	cout << num;
}