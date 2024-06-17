#include <stdio.h>
#pragma warning (disable:4996)

struct Node {
    int Address;
    int Data;
    int Next;
    Node* NextNode;
    Node(int a, int d, int n, Node* nn = NULL) {
        Address = a;
        Data = d;
        Next = n;
        NextNode = nn;
    }
};

Node* InsertNode(Node*& head, Node* temp, Node* unvisited) {
    if (head == NULL)
        head = temp;
    else if (head->Next == temp->Address) {
        temp->NextNode = head;
        head = temp;
    }
    else {
        Node* p = head;
        Node* q = head;
        int flag = 0;
        for (; p->NextNode != NULL;) {
            q = p;
            p = p->NextNode;
            if (p->Next == temp->Address) {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            temp->NextNode = p;
            q->NextNode = temp;
        }
        else {
            temp->NextNode = unvisited;
            unvisited = temp;
        }
    }
    return unvisited;
}

Node* ReInsert(Node*& head, Node* unvisited) {
    if (head == NULL)
        head = unvisited;
    else if (head->Next == unvisited->Address) {
        Node* temp = unvisited;
        unvisited = unvisited->NextNode;
        temp->NextNode = head;
        head = temp;
    }
    else {
        Node* p = head;
        Node* q = head;
        int flag = 0;
        for (; p->NextNode != NULL;) {
            q = p;
            p = p->NextNode;
            if (p->Next == unvisited->Address) {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {
            Node* temp = unvisited;  
            unvisited = unvisited->NextNode;
            temp->NextNode = p;
            q->NextNode = temp;
        }
    }
    return unvisited;
}

void PrintNode(Node* head) {
    Node* p = head;
    for (; p->NextNode != NULL; p = p->NextNode) {
        printf("%05d %d %05d\n", p->Address, p->Data, p->NextNode->Address);
    }
    printf("%05d %d %d", p->Address, p->Data, -1);
}

int main()
{
    int start, total;
    int s = scanf("%d%d", &start, &total);
    Node* head = NULL;
    Node* unvisited = NULL;
    int address, data, next;
    for (int i = 0; i < total; i++) {
        s = scanf("%d%d%d", &address, &data, &next);
        Node* temp = new Node(address, data, next);
        if (address == start) {
            head->NextNode = temp;
        }
        else {
            unvisited = InsertNode(head, temp, unvisited);
        }
    }
    while (unvisited != NULL)
        unvisited = ReInsert(head, unvisited);
    //cout << endl;
    //PrintNode(head);
    //cout << endl;
    PrintNode(head);
    return 0;
}
