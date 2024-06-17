#include <iostream>
using namespace std;

void to_lower(char* s) {
	for (int i = 0; s[i] != '\0'; i++) {
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] += 32;
	}
}

void delete_hyphen(char* s) {
	int i;
	for (i = 0; s[i] != '\0'; i++) {
		if ((s[i] == '-') || (i == 0 && s[i] == '\'')) {
				for (int j = i; s[j] != '\0'; j++)
					s[j] = s[j + 1];
		}
	}
	if (s[i - 1] == '\'')
		s[i - 1] = '\0';
}

bool str_equal(char* s1, char* s2) {
	int i;
	for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++) {
		if (s1[i] != s2[i])
			return false;
	}
	if (s1[i] != '\0' || s2[i] != '\0')
		return false;
	else
		return true;
}

int main()
{
	char s[1000], new_s[1000];
	char target[20], temp[20];
	char temp_lower[20];
	int i, j, count = 0, word = 0;
	cin.getline(target, 20);
	to_lower(target);
	delete_hyphen(target);
	cin.getline(s, 1000);
	for (i = 0; i < 1000; i++) {
		new_s[i] = '\0';
	}
	for (i = 0; s[i - 1] != '\0'; i++) {
		if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || s[i] == '-' || s[i] == '\'') {
			temp[word] = s[i];
			word++;
			count++;
		}
		else {
			if ((s[i - 1] >= 'a' && s[i - 1] <= 'z') || (s[i - 1] >= 'A' && s[i - 1] <= 'Z') || s[i - 1] == '-' || s[i - 1] == '\'') {
				temp[word] = '\0';
				for (j = 0; j < word; j++)
					temp_lower[j] = temp[j];
				temp_lower[word] = '\0';
				to_lower(temp_lower);
				delete_hyphen(temp_lower);
				count -= word;
				if (str_equal(temp_lower, target)) {
					if (temp[0] == '\'') {
						new_s[count] = '\'';
						count += 1;
					}
					new_s[count] = '2';
					new_s[count + 1] = '0';
					new_s[count + 2] = '2';
					new_s[count + 3] = '0';
					count += 4;
					if (temp[word - 1] == '\'') {
						new_s[count] = '\'';
						count += 1;
					}
				}
				else {
					for (j = 0; j < word; j++)
						new_s[count + j] = temp[j];
					count += word;
				}
				word = 0;
			}
			new_s[count] = s[i];
			count++;
		}

	}
	cout << new_s;
	return 0;
}