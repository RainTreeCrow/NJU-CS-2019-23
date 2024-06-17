#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int* whales = new int[n];
    bool exist = false;
    for (int i = 0; i < n; i++)
        cin >> whales[i];
    for (int i = 0; i < n - 2; i++) {
        for (int k = n - 1; k > i + 1; k--) {
            if (whales[i] < whales[k]) {
                for (int j = i + 1; j < k; j++) {
                    if (whales[j] > whales[k]) {
                        cout << "True";
                        return 0;
                    }
                }
            }
        }
    }
    cout << "False";
    return 0;
}