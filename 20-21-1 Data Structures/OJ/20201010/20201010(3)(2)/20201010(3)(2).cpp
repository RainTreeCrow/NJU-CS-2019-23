#include <stdio.h>
#pragma warning (disable:4996)

template <class E>
struct StackNode {                    //栈结点类定义
public:
    E data;			          //栈结点数据
    StackNode<E>* link;            //结点链指针
    StackNode(E d = 0, StackNode<E>* next = NULL)
        : data(d), link(next) { }
};

template <class E>
class LinkedStack { //链式栈类定义   
private:
    StackNode<E>* top;		            //栈顶指针
public:
    LinkedStack() { top = NULL; }	   //构造函数
    ~LinkedStack() { makeEmpty(); }   //析构函数
    void Push(E x);		             	   //进栈
    E Pop();			   //退栈
    E getTop() const;		//取栈顶  	
    bool IsEmpty() const { return top == NULL; }
    void makeEmpty();			//清空栈的内容
};

template <class E>
void LinkedStack<E>::makeEmpty() {
    //逐次删去链式栈中的元素直至栈顶指针为空。
    StackNode<E>* p;
    while (top != NULL)		//逐个结点释放
    {
        p = top;  top = top->link;  delete p;
    }
};

template <class E>
void LinkedStack<E>::Push(E x) {
    top = new StackNode<E>(x, top);	//创建新结点
};

template <class E>
E LinkedStack<E>::Pop() {
    //删除栈顶结点, 返回被删栈顶元素的值。
    if (IsEmpty() == true) return 0;   //栈空返回
    StackNode<E>* p = top;		//暂存栈顶元素
    top = top->link;			//退栈顶指针
    E x = p->data;   delete p;		//释放结点
    return x;
};

template <class E>
E LinkedStack<E>::getTop() const {
    if (IsEmpty() == true) return 0;   //栈空返回
    E x = top->data;                       //返回栈顶元素的值
    return x;
};

long long int Area() {
    long long int number;
    scanf("%lld", &number);
    long long int* column = new long long int[number + 1];
    long long int top;
    long long int temp;
    long long int max = 0;
    for (long long int i = 0; i < number; i++) {
        scanf("%lld", &column[i]);
    }
    column[number] = -1;
    LinkedStack<long long int> st;
    for (long long int i = 0; i < number + 1; i++) {
        if (st.IsEmpty() || column[st.getTop()] <= column[i])
            st.Push(i);
        else {
            while (!st.IsEmpty() && column[st.getTop()] > column[i]) {
                top = st.Pop();
                temp = (i - top) * column[top];
                if (temp > max)
                    max = temp;
            }
            st.Push(top);
            column[top] = column[i];
        }
    }
    return max;
}

int main()
{
    int round;
    scanf("%d", &round);
    long long int* result = new long long int[round];
    for (int i = 0; i < round; i++)
        result[i] = Area();
    for (int i = 0; i < round - 1; i++)
        printf("%lld\n", result[i]);
    printf("%lld", result[round - 1]);
    return 0;
}