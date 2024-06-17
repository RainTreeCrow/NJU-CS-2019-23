#include <iostream>
using namespace std;

int main()
{
    char list[1000];
    char result[1000];
    for (int i = 0; i < 1000; i++)
        result[i] = '\0';
    cin >> list;
    int len = 0, count = 0, temp = 1;
    for (int i = 0; list[i] != '\0'; ) {
        for (int j = i + 1; list[j] != '\0'; j++) {
            if (list[j] != list[i]) {
                if (temp == 1) {
                    result[count] = list[i];
                    count += 1;
                }
                else {
                    result[count] = temp + '0';
                    result[count + 1] = list[i];
                    count += 2;
                }
                i += temp;
                temp = 1;
                break;
            }
            else
                temp += 1;
        }
        if (list[i + temp] == '\0') {
            if (temp == 1) {
                result[count] = list[i];
                count += 1;
            }
            else {
                result[count] = temp + '0';
                result[count + 1] = list[i];
                count += 2;
            }
            break;
        }
    }
    result[count] = '\0';
    cout << result;
    return 0;
}