#include <iostream>
using namespace std;

int main()
{
    int count;
    cin >> count;
    int* list = new int[count];
    for (int i = 0; i < count; i++)
        cin >> list[i];
    for (int i = 0; i < count; i++) {
        int index = list[i];
        if (index == 1)
            cout << 1 << endl;
        else {
            int* result = new int[index];
            int count = 1, temp = 0, flag;
            for (int i = 0; i < index; i++) {
                result[i] = 0;
            }
            for (int i = 1; i < index; i += 2) {
                result[i] = count;
                count += 1;
            }
            if (index % 2 != 0)
                temp = index - 1;
            else
                temp = 0;
            flag = 0;
            while (count <= index) {
                if (!result[temp] && flag == 1) {
                    result[temp] = count;
                    count += 1;
                    flag = 0;
                }
                else if (!result[temp])
                    flag = 1;
                temp = (temp + 1) % index;
            }
            for (int i = 0; i < index - 1; i++)
                cout << result[i] << ' ';
            cout << result[index - 1] << endl;
        }
    }
    return 0;
}