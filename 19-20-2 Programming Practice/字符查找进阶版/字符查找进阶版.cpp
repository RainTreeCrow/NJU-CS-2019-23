#include <iostream>
using namespace std;

int main()
{
	char s[100];
	int i, j, k, temp_l, temp_n, total = 0;
	int alphabet[52][2];
	char most;
	for (i = 0; i < 52; i++) {
		alphabet[i][0] = i;
		alphabet[i][1] = 0;
	}
	cin >> s >> k;
	for (i = 0; s[i] != '\0'; i++) {
		if (s[i] >= 'A' && s[i] <= 'Z')
			alphabet[s[i] - 65][1] += 1;
		else if (s[i] >= 'a' && s[i] <= 'z')
			alphabet[s[i] - 97 + 26][1] += 1;
		else {
			cout << "字符流不合法" << endl;
			return -1;
		}
	}
	for (i = 0; i < 52; i++) {
		if (alphabet[i][1] != 0)
			total += 1;
		for (j = 0; j < 51 - i; j++) {
			if (alphabet[j][1] > alphabet[j + 1][1]) {
				temp_l = alphabet[j][0];
				temp_n = alphabet[j][1];
				alphabet[j][0] = alphabet[j + 1][0];
				alphabet[j][1] = alphabet[j + 1][1];
				alphabet[j + 1][0] = temp_l;
				alphabet[j + 1][1] = temp_n;
			}
		}
	}
	if (total < k) {
		cout << "次数不合法" << endl;
		return -1;
	}
	if (alphabet[52 - k][0] >= 26)
		most = 'a' + alphabet[52 - k][0] - 26;
	else
		most = 'A' + alphabet[52 - k][0];
	cout << most << ' ' << alphabet[52 - k][1];
	return 0;
}