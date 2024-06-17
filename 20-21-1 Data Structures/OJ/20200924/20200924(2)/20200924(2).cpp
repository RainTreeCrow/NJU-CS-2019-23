#include <iostream>
using namespace std;

struct whale {
    int number;
    whale* pre;
    whale* next;
    whale(int i, whale* p = NULL, whale* n = NULL) {
        number = i;
        pre = p;
        next = n;
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
    void insert(int i, whale* pos, bool next) {
        whale* w = new whale(i);
        if (next) {
            if (pos == NULL) {
                w->next = head;
                head = w;
            }
            else {
                if (tail == pos)
                    tail = w;
                w->next = pos->next;
                pos->next = w;
                w->pre = pos;
                if (w->next) w->next->pre = w;
            }
        }
        else {
            if (pos == NULL) {
                w->pre = tail;
                tail = w;
            }
            else {
                if (head == pos)
                    head = w;
                w->pre = pos->pre;
                pos->pre = w;
                w->next = pos;
                if (w->pre) w->pre->next = w;
            }
        }
        length += 1;
    }
    int get_length() {
        return length;
    }
    whale* get_whale(int index) {
        whale* p;
        for (p = head; p != NULL; p = p->next) {
            if (p->number == index)
                break;
        }
        return p;
    }
    void print() {
        for (whale* p = head; p != NULL; p = p->next)
            cout << p->number << ' ';
        cout << endl;
    }
};

int main()
{
    int num, index = 0;
    cin >> num;
    int** student = new int*[num];
    queue Q;
    for (int i = 0; i < num; i++) {
        student[index] = new int[2];
        cin >> student[index][0] >> student[index][1];
        if (student[index][1] == 0)
            Q.insert(student[index][0], NULL, 1);
        else index += 1;
    }
    while (Q.get_length() < num) {
        for (int i = 0; i < num - 1; i++) {
            whale* pre = Q.get_whale(student[i][1]);
            whale* next = Q.get_whale(student[i][0]);
            if (pre != NULL)
                Q.insert(student[i][0], pre, 1);
            else if (next != NULL)
                Q.insert(student[i][1], next, 0);
            if (Q.get_length() == num) break;
        }
    }
    Q.print();
    return 0;
}