#include <iostream>
using namespace std;

template <class E>
struct StackNode {
public:
    E data;
    StackNode<E>* link;
    StackNode(E d = 0, StackNode<E>* next = NULL)
        : data(d), link(next) { }
};

template <class E>
class LinkedStack {  
private:
    StackNode<E>* top;
public:
    LinkedStack() { top = NULL; }
    ~LinkedStack() { makeEmpty(); }
    void Push(E x);
    bool Pop(E &x);
    bool getTop(E &x) const; 	
    bool IsEmpty() const { return top == NULL; }
    void makeEmpty();
};

template <class E>
void LinkedStack<E>::makeEmpty() {
    StackNode<E>* p;
    while (top != NULL) {
        p = top;
        top = top->link;
        delete p;
    }
};

template <class E>
void LinkedStack<E>::Push(E x) {
    top = new StackNode<E>(x, top);
};

template <class E>
bool LinkedStack<E>::Pop(E &x) {
    if (IsEmpty() == true) return false;
    StackNode<E>* p = top;
    top = top->link;
    x = p->data;
    delete p;
    return true;
};

template <class E>
bool LinkedStack<E>::getTop(E &x) const {
    if (IsEmpty() == true) return false;
    x = top->data;
    return true;
};

int isp(char ch) {
    switch (ch) {
    case ';': return 0;
    case '(': return 1;
    case 'x': return 5;
    case '+':
    case '-': return 3;
    case ')': return 6;
    }
}

int icp(char ch) {
    switch (ch) {
    case ';': return 0;
    case '(': return 6;
    case 'x': return 4;
    case '+':
    case '-': return 2;
    case ')': return 1;
    }
}

char* Process(char* line) {
    LinkedStack<char> St;
    St.Push(';');
    char ch, top;
    char* result = new char[100];
    int index = 0;
    for (int i = 0; line[i] != '\0';) {
        ch = line[i];
        if (ch >= '0' && ch <= '9') {
            result[index] = ch;
            index += 1;
            i++;
        }
        else {
            St.getTop(top);
            if (icp(ch) > isp(top)) {
                St.Push(ch);
                i++;
            }
            else if (icp(ch) < isp(top)) {
                St.Pop(result[index]);
                index += 1;
            }
            else {
                St.Pop(top);
                if (top == '(' || top == ';') i++;
            }
        }
    }
    result[index] = '\0';
    return result;
}

class Calculator {
    LinkedStack<int> S;
public:
    Calculator() { };
    ~Calculator() { S.makeEmpty(); }
    void Run(char* line);
    bool Get2Operands(int &a, int &b);
    void DoOperator(char ch);
};

void Calculator::Run(char* line) {
    char ch;
    int newoperand;
    for (int i = 0; line[i] != '\0'; i++) {
        ch = line[i];
        switch (ch) {
        case '+':
        case '-':
        case 'x':
            DoOperator(ch);
            break;
        default:
            newoperand = ch - '0';
            S.Push(newoperand);
        }
    }
    int res;
    if (S.getTop(res))
        cout << res << endl;
}

bool Calculator::Get2Operands(int& a, int& b) {
    bool bok = S.Pop(b);
    bool aok = S.Pop(a);
    if (aok && bok) return true;
    else return false;
}

void Calculator::DoOperator(char op) {
    int left, right;
    bool result;
    result = Get2Operands(left, right);
    if (!result) return;
    switch (op) {
    case '+': S.Push(left + right);  break;
    case '-': S.Push(left - right);  break;
    case 'x': S.Push(left * right);  break;
    }
}

int main()
{
    Calculator cal;
    char* line = new char[100];
    while (cin.getline(line, 100)) {
        int len = strlen(line);
        line[len] = ';';
        line[len + 1] = '\0';
        //cout << line << endl;
        char* result = Process(line);
        //cout << result << endl;
        cal.Run(result);
        return 0;
    }
}