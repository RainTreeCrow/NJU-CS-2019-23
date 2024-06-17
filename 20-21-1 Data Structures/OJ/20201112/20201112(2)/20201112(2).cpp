#include <stdio.h>
#pragma warning(disable:4996)

double MAX_SCORE = 0;

struct BinTreeNode {
    int total;
    int count;
    BinTreeNode* parent, * leftChild, * rightChild;
    BinTreeNode(int score) {
        total = score;  count = 1; parent = NULL;
        leftChild = NULL;  rightChild = NULL;
    }
};

class BinaryTree {
public:
    BinaryTree(int ref) : refValue(ref), root(NULL) { }
    ~BinaryTree() { destroy(root); }
    void CreateBinTree(int* list, int len) {
        if (len == 0)
            root = NULL;
        else {
            BinTreeNode** stack = new BinTreeNode * [len];
            stack[0] = new BinTreeNode(list[0]);
            int index = 0, count = 1;
            bool left = true;
            for (int i = 1; i < len; i++) {
                if (list[i] == refValue) {
                    if (left) {
                        stack[index]->leftChild = NULL;
                        left = false;
                    }
                    else {
                        stack[index++]->rightChild = NULL;
                        left = true;
                    }
                }
                else {
                    BinTreeNode* temp = new BinTreeNode(list[i]);
                    temp->parent = stack[index];
                    if (left) {
                        stack[index]->leftChild = temp;
                        left = false;
                    }
                    else {
                        stack[index++]->rightChild = temp;
                        left = true;
                    }
                    BinTreeNode *p = temp->parent;
                    while (p != NULL) {
                        p->total += temp->total;
                        p->count++;
                        p = p->parent;
                    }
                    stack[count++] = temp;
                }
            }
            root = stack[0];
        }

    }
    void maxScore() {
        updateScore(root);
    }
protected:
    int refValue;
    BinTreeNode* root;
    void destroy(BinTreeNode*& subTree) {
        if (subTree != NULL) {
            destroy(subTree->leftChild);
            destroy(subTree->rightChild);
            delete subTree;
        }
    }
    void updateScore(BinTreeNode* subTree) {
        if (subTree != NULL) {
            double tempScore = (double)subTree->total / subTree->count;
            if (tempScore > MAX_SCORE)
                MAX_SCORE = tempScore;
            updateScore(subTree->leftChild);
            updateScore(subTree->rightChild);
        }
    }
};

int main()
{
    BinaryTree family(-1);
    int* list = new int[5000];
    int len = 0, count = 0;
    while (count != -1) {
        scanf("%d", &list[len]);
        if (list[len] == -1) count--;
        else count++;
        len++;
    }
    family.CreateBinTree(list, len);
    family.maxScore();
    printf("%.5f", MAX_SCORE);
    return 0;
}