#include <iostream>
using namespace std;

int main()
{
	char s[100];
	int i, max_index = 0, max_num = 0;
	int alphabet[52];
	char most;
	for (i = 0; i < 52; i++)
		alphabet[i] = 0;
	cin >> s;
	for (i = 0; s[i] != '\0'; i++) {
		if (s[i] >= 'A' && s[i] <= 'Z')
			alphabet[s[i] - 65] += 1;
		else if (s[i] >= 'a' && s[i] <= 'z')
			alphabet[s[i] - 97 + 26] += 1;
		else {
			cout << "字符流不合法" << endl;
			return -1;
		}
	}
	for (i = 0; i < 52; i++) {
		if (alphabet[i] >= max_num) {
			max_index = i;
			max_num = alphabet[i];
		}
	}
	if (max_index >= 26)
		most = 'a' + max_index - 26;
	else
		most = 'A' + max_index;
	cout << most << ' ' << max_num;
	return 0;
}