#include <iostream>
using namespace std;

int min_length(char s[])
{
	int num = 0;
	while (s[num] != '\0')
		num += 1;
	if (num % 2 != 0)
		return num;
	else {
		bool mirror = true;
		for (int i = 0; i < num / 2; i++) {
			if (s[i] != s[num - i - 1]) {
				mirror = false;
				break;
			}
		}
		if (mirror) {
			for (int i = num / 2; i < num; i++)
				s[i] = '\0';
			return min_length(s);
		}
		else
			return num;
	}
		
}

int main()
{
	char* s = new char[50];
	cin >> s;
	cout << min_length(s);
	return 0;
}