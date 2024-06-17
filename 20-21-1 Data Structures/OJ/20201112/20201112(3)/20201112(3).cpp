#include <iostream>
#include <string.h>
using namespace std;

struct Node {
    int index;
    int count;
    Node* next;
    Node* child;
    Node(int i, int c, Node* n = NULL, Node* ch = NULL) {
        index = i; count = c; next = n; child = ch;
    }
};

void Insert(Node*& head, Node*& p) {
    if (head == NULL) {
        head = p;
    }
    else if (p->count < head->count) {
        p->next = head;
        head = p;
    }
    else {
        Node* cur = head;
        Node* pre;
        while (1) {
            pre = cur;
            cur = cur->next;
            if (cur == NULL || p->count < cur->count) {
                pre->next = p;
                p->next = cur;
                break;
            }
        }
    }
}

int main()
{
    char* string = new char[100000];
    int* alphabetCount = new int[26];
    bool* alphabetTag = new bool[26];
    Node* head = NULL;
    int* alphabetLength = new int[26];
    for (int i = 0; i < 26; i++) {
        alphabetCount[i] = 0;
        alphabetTag[i] = 1;
        alphabetLength[i] = 0;
    }
    int count = 0;
    cin >> string;
    for (int i = 0; i < strlen(string); i++)
        alphabetCount[string[i] - 'A']++;
    while (count < 26) {
        int max = 0;
        int maxIndex = -1;
        for (int i = 0; i < 26; i++) {
            if (alphabetTag[i] && alphabetCount[i] > max) {
                max = alphabetCount[i];
                maxIndex = i;
            }
        }
        alphabetTag[maxIndex] = 0;
        count++;
        if (max != 0) {
            if (head == NULL)
                head = new Node(maxIndex, max);
            else
                head = new Node(maxIndex, max, head);
        }
    }
    while (head->next != NULL) {
        Node* temp;
        Node* temp1 = head;
        Node* temp2 = head->next;
        head = head->next->next;
        temp2->next = NULL;
        if (temp2->index == -1)
            temp = temp2->child;
        else temp = temp2;
        if (temp1->index == -1) {
            Node*p = temp1->child;
            while (p->next != NULL)
                p = p->next;
            p->next = temp;
            temp = temp1->child;
        }
        else {
            temp1->next = temp;
            temp = temp1;
        }
        Node* p = new Node(-1, temp1->count + temp2->count, NULL, temp);
        for (Node* q = temp; q != NULL; q = q->next)
            alphabetLength[q->index]++;
        Insert(head, p);
    }
    int len = 0;
    for (int i = 0; i < 26; i++) 
        len += alphabetLength[i] * alphabetCount[i];
    cout << len;
    return 0;
}