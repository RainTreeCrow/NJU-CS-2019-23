#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

short** Case;
vector<char> Sequence;
vector<char> Reversed;

int MaxSubSeq(int n) {
    Case = new short* [n + 1];
    for (short i = 0; i <= n; i++) {
        Case[i] = new short[n + 1];
    }
    for (short i = 0; i <= n; i++) {
        Case[0][i] = 0;
        Case[i][0] = 0;
    }
    for (short i = 1; i <= n; i++) {
        for (short j = 1; j <= n; j++) {
            if (Sequence[i] == Reversed[j])
                Case[i][j] = Case[i - 1][j - 1] + 1;
            else
                Case[i][j] = max(Case[i - 1][j], Case[i][j - 1]);
        }
    }
    return Case[n][n];
}

int main()
{
    short n = 0;
    string input;
    if (getline(cin, input)) {
        char ch;
        stringstream inputStream(input);
        Sequence.push_back(',');
        while (inputStream >> ch) {
            Sequence.push_back(ch);
            Reversed.push_back(ch);
            n++;
        }
        Reversed.push_back('.');
    }
    reverse(Reversed.begin(), Reversed.end());
    short result = MaxSubSeq(n);
    cout << "I have read the rules about plagiarism punishment" << endl;
    cout << result;
    return 0;
}