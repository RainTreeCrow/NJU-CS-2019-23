#include <iostream>
using namespace std;

struct whale {
    int number;
    whale* next;
    whale(int n, whale* w = NULL) {
        number = n;
        next = w;
    }
};

class queue {
    whale* head;
    whale* tail;
    int length;
public:
    queue() {
        head = NULL;
        tail = NULL;
        length = 0;
    }
    void insert(int i) {
        whale* w = new whale(i);
        if (head == NULL) {
            head = w;
            tail = w;
        }
        else {
            tail->next = w;
            tail = tail->next;
        }
        length += 1;
    }
    void del(int i) {
        whale* p = head, * q = head;
        for (p = head; p != NULL;) {
            q = p;
            p = p->next;
            if (p->number == i)
                break;
        }
        if (p != NULL) {
            if (p == head) {
                head = head->next;
                delete p;
            }
            else if (p == tail) {
                tail = q;
                q->next = NULL;
                delete p;
            }
            else {
                q->next = p->next;
                delete p;
            }
            length -= 1;
        }
    }
    int get_length() {
        return length;
    }
    whale* get_whale(int index) {
        if (index <= 0 || index >= length)
            exit(-1);
        else {
            whale* p = head;
            for (int i = 1; i < index; i++)
                p = p->next;
            return p;
        }
    }
    void print() {
        for (whale* p = head; p != NULL; p = p->next)
            cout << p->number << endl;
    }
};

int main()
{
    int num;
    int max = 2;
    queue Q;
    queue Go;
    Q.insert(2);
    for (int i = 3; i <= 40000; i += 2) {
        Q.insert(i);
    }
    cin >> num;
    while (num != 0) {
        if (num <= max)
            Go.insert(Q.get_whale(num)->number);
        else {
            whale* c = Q.get_whale(max);
            whale* d = NULL;
            int circle;
            if (c == NULL)
                circle = 0;
            else
                circle = c->number;
            while (num > max) {
                int count = 0;
                while (c != NULL) {
                    d = c;
                    c = c->next;
                    if (count == circle) {
                        Q.del(d->number);
                        count = 1;
                    }
                    else count++;
                }
                max += 1;
                c = Q.get_whale(max);
                if (c != NULL)
                    circle = c->number;
            }
            Go.insert(Q.get_whale(num)->number);
        }
        cin >> num;
    }
    Go.print();
    return 0;
}