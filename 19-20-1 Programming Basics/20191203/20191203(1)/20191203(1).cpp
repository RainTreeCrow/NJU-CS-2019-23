#include <iostream>
using namespace std;

char* del(char s[], char c)
{
	for (int i = 0; s[i] != '\0'; i++){
		if (s[i] == c) {
			for (int j = i; s[j] != '\0'; j++)
				s[j] = s[j + 1];
		}
	}
	return s;
}

int main()
{
	char* s = new char[100];
	char c;
	cin >> s;
	cin >> c;
	cout << del(s, c);
	return 0;
}