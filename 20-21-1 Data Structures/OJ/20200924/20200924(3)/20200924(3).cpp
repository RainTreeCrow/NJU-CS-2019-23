#include <iostream>
#include <string.h>
using namespace std;

bool overflow = 0;

struct digit {
    int dig;
    digit* pre;
    digit* next;
    digit(int d, digit* p = NULL, digit* n = NULL) {
        dig = d;
        pre = p;
        if (pre) pre->next = this;
        next = n;
        if (next) next->pre = this;
    }
};

class number {
    digit* head;
    digit* tail;
    int length;
    friend char* cal(number x, number y);
public:
    number() {
        head = NULL;
        tail = NULL;
        length = 0;
    }
    number(char* str) {
        length = strlen(str);
        head = new digit(str[0] - 48, NULL, NULL);
        tail = head;
        for (int i = 1; i < length; i++) {
            digit* temp = new digit(str[i] - 48, NULL, head);
            head = temp;
        }
    }
};

char* cal(number x, number y) {
    bool swi = 0;
    if (x.length < y.length)
        swi = 1;
    else if (x.length == y.length) {
        digit* a = x.tail;
        digit* b = y.tail;
        for (; a != NULL; a = a->pre) {
            if (a->dig < b->dig) {
                swi = 1;
                break;
            }
            else if (a->dig > b->dig) {
                swi = 0;
                break;
            }
            else b = b->pre;
        }
    }
    if (swi) {
        number temp = x;
        x = y;
        y = temp;
        overflow = 1;
    }
    char* result = new char[x.length];
    digit* d = y.head;
    digit* e = x.head;
    int t, cin = 0, i = x.length - 1;
    for (; d != NULL; d = d->next) {
        t = e->dig - d->dig - cin;
        if (t < 0) {
            t += 10;
            cin = 1;
        }
        else cin = 0;
        result[i] = t + 48;
        i--;
        e = e->next;
        //cout << e->dig << ' ' << d->dig << ' ' << cin << ' ' << t << endl;
    }
    while (i >= 0) {
        t = e->dig - cin;
        if (t < 0) {
            t += 10;
            cin = 1;
        }
        else cin = 0;
        result[i] = t + 48;
        i--;
        e = e->next;
    }
    result[x.length] = '\0';
    return result;
}

int main()
{
    char* a = new char[300];
    char* b = new char[300];
    cin >> a >> b;
    number a1(a);
    number b1(b);
    char* result = cal(a1, b1);
    if (overflow)
        cout << '-';
    unsigned i = 0;
    while (result[i] == '0') i++;
    if (i == strlen(result))
        cout << '0';
    else
        for (i; i < strlen(result); i++)
            cout << result[i];
    cout << endl;
    return 0;
}