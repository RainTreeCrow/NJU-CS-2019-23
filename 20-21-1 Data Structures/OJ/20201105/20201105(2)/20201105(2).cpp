#include <iostream>
#include <string.h>
using namespace std;

struct indexNode {
    int index;
    indexNode* next;
    indexNode(int i, indexNode* n = NULL) {
        index = i; next = n;
    }
};

void getNext(string T, int*& next) {
    int j = 0, k = -1, lengthP = T.length();
    next[0] = -1;
    while (j < lengthP) {
        if (k == -1 || T[j] == T[k]) {
            j++;  k++;
            next[j] = k;
        }
        else k = next[k];
    }
}

int fastFind(string& T, string& pat, int k, int next[]) {
    //从 k 开始寻找 pat 在 this 串中匹配的位置。若找到，函数返回 pat 在 this 串中开始位置，
    //否则函数返回-1。数组next[ ] 存放 pat 的next[j] 值。
    int posP = 0, posT = k;                                 //两个串的扫描指针
    int lengthP = pat.length();                             //模式串长度
    int lengthT = T.length();                               //目标串长度
    while (posP < lengthP && posT < lengthT)
        if (posP == -1 || pat[posP] == T[posT]) {
            posP++;  posT++;
        }
        else posP = next[posP];                 //求pat下趟比较位置
    if (posP < lengthP) return -1;	            //匹配失败
    else return posT - lengthP;		            //匹配成功
}

int main()
{
    string T, pat;
    cin >> T >> pat;
    int k = 0, temp;
    indexNode* head = NULL, * tail = NULL;
    int* next = new int[T.length()];
    getNext(T, next);
    while (k < T.length()) {
        temp = fastFind(T, pat, k, next);
        if (temp == -1) break;
        else {
            if (head == NULL) {
                head = new indexNode(temp);
                tail = head;
            }
            else {
                tail->next = new indexNode(temp);
                tail = tail->next;
            }
            k = temp + 1;
        }
    }
    if (head == NULL && tail == NULL)
        cout << -1;
    else {
        for (indexNode* i = head; i != tail; i = i->next)
            cout << i->index << ' ';
        cout << tail->index;
    }
    return 0;
}