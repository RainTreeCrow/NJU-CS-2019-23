#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>
using namespace std;

/*
int gcd(int a, int b) {
    if (a % b == 0)
        return b;
    else
        return gcd(b, a % b);
}

int factorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}

int fact_tail(int n, int m) {
    if (n == 0 || n == 1)
        return m;
    else
        return fact_tail(n - 1, m * n);
}

int main()
{
    int a, b, c;
    cin >> a >> b;
    c = a % b;
    while (c) {
        a = b;
        b = c;
        c = a % b;
    }
    cout << b << endl;
    cout << gcd(a, b) << endl;
    int n, m = 1;
    cin >> n;
    for (int i = 1; i <= n; i++)
        m *= i;
    cout << m << endl;
    cout << factorial(n) << endl;
    cout << fact_tail(n, 1) << endl;
    return 0;
}
*/

/*
char upper(char ch) {
    if (ch >= 'a' && ch <= 'z')
        return ch -= 32;
    else
        return ch;
}

string s_upper(string s) {
    string s_new;
    s_new.resize(s.size());
    transform(s.begin(), s.end(), s_new.begin(), upper);
    return s_new;
}

int main() {
    string s_old, s_new;
    cin >> s_old;
    s_new.resize(s_old.size());
    for (int i = 0; i < s_old.size(); i++) {
        if (s_old[i] >= 'a' && s_old[i] <= 'z')
            s_new[i] = s_old[i] - 32;
        else
            s_new[i] = s_old[i];
    }
    cout << s_new << endl;
    cout << s_upper(s_old) << endl;
    return 0;
}
*/

/*
int multiply(vector <int> nums) {
    int product = accumulate(nums.begin(), nums.end(), 1,
        [](int a, int x) { return a * x; });
    return product;
}

int main()
{
    int temp;
    vector <int> nums;
    for (int i = 0; i < 10; i++) {
        cin >> temp;
        nums.push_back(temp);
    }
    int product = 1;
    vector<int>::iterator iter;
    for (iter = nums.begin(); iter != nums.end(); iter++) {
        product *= *iter;
    }
    cout << product << endl;
    cout << multiply(nums) << endl;
    return 0;
}
*/

string make_url(string protocol, string latter) {
    return protocol + latter;
}

function<string(string)> make_url_curry(string protocol) {
    return [protocol](string latter) { return make_url(protocol, latter); };
}

int main() {
    string protocol, latter;
    cin >> protocol >> latter;
    cout << make_url(protocol, latter) << endl;
    function < string(string)> make_with = make_url_curry("https://");
    cout << make_with(latter) << endl;
    return 0;
}