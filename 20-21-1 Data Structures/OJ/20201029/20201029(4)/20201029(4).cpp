#include <iostream>
#include <string.h>
using namespace std;
#pragma warning(disable:4996)

struct Node {
    int index;
    Node* pre;
    Node* next;
    Node(int i, Node* p = NULL, Node* n = NULL) {
        index = i;
        pre = p;
        next = n;
    }
};

void insert(Node* head, Node* temp) {
    for (Node* p = head; p != NULL; p = p->next) {
        if (temp->index < p->index && temp->index > p->next->index) {
            temp->next = p->next;
            p->next = temp;
            temp->pre = p;
            if (temp->next)
                temp->next->pre = temp;
            break;
        }
    }
}

int main()
{
    char* list = new char[5000000];
    cin >> list;
    char c;
    bool exist = false;
    int len = strlen(list);
    Node* tail = new Node(-1);
    Node* head = new Node(len, NULL, tail);
    tail->pre = head;
    int i, j;
    for (i = 0; i < 26; i++) {
        c = i + 'a';
        for (Node* p = head; p != tail; p = p->next) {
            Node* q = p->next;
            for (j = q->index + 1; j < p->index; j++) {
                if (list[j] == c) {
                    exist = true;
                    break;
                }
            }
            if (exist)
                break;
        }
        if (exist) {
            Node* temp = new Node(j);
            insert(head, temp);
            exist = false;
        }
    }
    for (Node* p = tail->pre; p != head; p = p->pre) {
        cout << list[p->index];
    }
    return 0;
}