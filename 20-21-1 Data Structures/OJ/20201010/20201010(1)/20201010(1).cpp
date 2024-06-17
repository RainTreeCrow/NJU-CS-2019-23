#include <stdio.h>
#pragma warning (disable:4996)

struct Node {
    int Address;
    int Data;
    int Next;
    Node* Left;
    Node* Right;
    Node(int a, int d, int n, Node* l = NULL, Node* r = NULL) {
        Address = a;
        Data = d;
        Next = n;
        Left = l;
        Right = r;
    }
};

void InsertNode(Node* &head, Node* temp) {
    if (head == NULL)
        head = temp;
    else {
        Node* p = head;
        bool right = true;
        for (; p->Right != NULL; p = p->Right) {
            if (p->Next == temp->Address)
                break;
            else if (temp->Next == p->Address) {
                right = false;
                break;
            }
        }
        if (right) {
            temp->Right = p->Right;
            p->Right = temp;
            temp->Left = p;
            if (temp->Right != NULL)
                temp->Right->Left = temp;
        }
        else {
            temp->Left = p->Left;
            p->Left = temp;
            temp->Right = p;
            if (temp->Left != NULL)
                temp->Left->Right = temp;
        }
    }
}

void ReverseNode(Node* &head) {
    Node* p = head;
    head->Next = -1;
    Node* q;
    for (; p!= NULL;) {
        q = p->Right;
        p->Right = p->Left;
        p->Left = q;
        if (q != NULL)
            q->Next = p->Address;
        else
            head = p;
        p = q;
    }
}

void PrintNode(Node* head) {
    for (Node* p = head; p != NULL; p = p->Right) {
        if (p->Next == -1)
            printf("%05d %d %d", p->Address, p->Data, p->Next);
        else
            printf("%05d %d %05d\n", p->Address, p->Data, p->Next);
    }
}

int main()
{
    int start, total;
    scanf("%d%d", &start, &total);
    Node* head = NULL;
    int address, data, next;
    for (int i = 0; i < total; i++) {
        scanf("%d%d%d", &address, &data, &next);
        Node* temp = new Node(address, data, next);
        if (address == start) {
            temp->Right = head;
            if (head != NULL)
                head->Left = temp;
            head = temp;
        }
        else {
            InsertNode(head, temp);
        }
    }
    //cout << endl;
    //PrintNode(head);
    //cout << endl;
    ReverseNode(head);
    PrintNode(head);
    return 0;
}