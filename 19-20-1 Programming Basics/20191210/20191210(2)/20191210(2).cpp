#include <iostream>
#include <string>
using namespace std;

int main()
{
	string s;
	getline(cin, s);
	int l = 0, max = 0, max_index = 0, remain = s.length() - 1;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == ' ') {
			remain -= l + 1;
			if (l > max) {
				max = l;
				max_index = i - max;
			}
			l = 0;
			continue;
		}
		l += 1;
	}
	if (remain > max) {
		max = remain;
		max_index = s.length() - remain - 1;
	}
	for (int i = 0; i < max; i++)
		cout << s[max_index + i];
	return 0;
}