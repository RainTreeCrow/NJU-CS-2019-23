#include <iostream>
#include <string.h>
using namespace std;
#pragma warning(disable:4996)

int main()
{
    char* list = new char[5000000];
    cin >> list;
    int len = strlen(list);
    int* count = new int[26];
    bool* visited = new bool[26];
    char result[100] = "\0";
    int index = -1;
    for (int i = 0; i < 26; i++) {
        count[i] = 0;
        visited[i] = false;
    }
    for (int i = 0; i < len; i++) {
        count[list[i] - 'a'] += 1;
    }
    for (int i = 0; i < len; i++) {
        count[list[i] - 'a'] -= 1;
        if (!visited[list[i] - 'a']) {
            while (index >= 0 && count[result[index] - 'a'] > 0 && result[index] > list[i]) {
                visited[result[index] - 'a'] = false;
                index -= 1;
            }
            index += 1;
            result[index] = list[i];
            visited[list[i] - 'a'] = true;
        }
    }
    index += 1;
    result[index] = '\0';
    cout << result;
    return 0;
}