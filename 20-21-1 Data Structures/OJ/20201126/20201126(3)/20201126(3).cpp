#include <stdio.h>
#include <cmath>
#pragma warning (disable:4996)

struct Node {
    float distance;
    Node* next;
    Node(float d, Node* n = NULL) {
        distance = d;  next = n;
    }
};

void insert(Node*& head, Node*& temp) {
    if (head == NULL)
        head = temp;
    else if (temp->distance <= head->distance) {
        temp->next = head;
        head = temp;
    }
    else {
        Node* pre = head;
        Node* cur = pre->next;
        while (cur->distance < temp->distance) {
            pre = cur;
            cur = cur->next;
        }
        temp->next = cur;
        pre->next = temp;
    }
}

void insertTail(Node*& head, Node*& tail, Node*& temp) {
    if (head == NULL) {
        head = temp;
        tail = temp;
    }
    else {
        tail->next = temp;
        tail = temp;
    }
}

int main()
{
    int m;
    scanf("%d", &m);
    float a, b, c;
    Node* points[200];
    for (int i = 0; i < 200; i++)
        points[i] = NULL;
    float temp;
    int index;
    int count;
    Node* result = NULL;
    Node* tail = NULL;
    while (m > 0) {
        char ch;
        scanf("%c", &ch);
        if (ch == 'A') {
            scanf("%f", &a);
            scanf("%f", &b);
            scanf("%f", &c);
            temp = sqrtf(a * a + b * b + c * c);
            //printf("%f\n", temp);
            Node* tempNode = new Node(temp);
            index = temp * 100;
            insert(points[index], tempNode);
            m--;
        }
        else if (ch == 'Q') {
            scanf("%d", &count);
            int j = 0;
            int flag = count;
            float total = 0;
            while (flag > 0) {
                Node* p = points[j];
                while (p != NULL) {
                    total += p->distance;
                    Node* q = p;
                    p = p->next;
                    delete q;
                    flag--;
                    if (flag == 0)
                        break;
                }
                points[j] = p;
                j++;
            }
            float res = total / count;
            Node* r = new Node(res);
            insertTail(result, tail, r);
            m--;
        }
    }
    Node* s = result;
    while (s != NULL) {
        printf("%.5f\n", s->distance);
        s = s->next;
    }
    return 0;
}