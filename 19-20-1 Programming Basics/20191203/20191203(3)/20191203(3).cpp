#include <iostream>
using namespace std;

void replace(char *s)
{
	int i = 0;
	for (int j = 0; s[j] != '\0'; j++) {
		if (s[j] == 'y' && s[j + 1] == 'o' && s[j + 2] == 'u') {
			cout << "we";
			j += 2;
		}
		else
			cout << s[j];
	}
}

int main()
{
	char s[100];
	cin.get(s, 100);
	replace(s);
	return 0;
}