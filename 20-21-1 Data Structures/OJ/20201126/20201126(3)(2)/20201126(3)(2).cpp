#include <iostream>
#include <cmath>
#pragma warning (disable:4996)

#define DefaultSize 10000000

struct Node {
    double distance;
    Node* next;
    Node(double d, Node* n = NULL) {
        distance = d;  next = n;
    }
};

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

template <class T, class E>
class MinPQ {         //最小优先级队列类的定义
public:
    virtual bool Insert(E& d) = 0;
    virtual bool Remove(E& d) = 0;
};

template <class T, class E>
class MinHeap : public MinPQ<T, E> {
    //最小堆继承了（最小）优先级队列
public:
    MinHeap(int sz = DefaultSize);	//构造函数
    MinHeap(E arr[], int n);		//构造函数
    ~MinHeap() { /*delete[] heap;*/ }	//析构函数
    bool Insert(E& x);			//插入
    bool Remove(E& d);			//删除
    bool IsEmpty() const		//判堆空否
    {
        return  currentSize == 0;
    }
    bool IsFull() const		//判堆满否
    {
        return currentSize == maxHeapSize;
    }
    void MakeEmpty() { currentSize = 0; }	//置空堆
private:
    E* heap;			//最小堆元素存储数组
    int currentSize;		//最小堆当前元素个数
    int maxHeapSize;	//最小堆最大容量
    void siftDown(int start, int m);	//调整算法
    void siftUp(int start);		          //调整算法
};

template <class T, class E>
MinHeap<T, E>::MinHeap(int sz) {
    maxHeapSize = (DefaultSize < sz) ?
        sz : DefaultSize;
    heap = new E[maxHeapSize];  	//创建堆空间
    if (heap == NULL) {
        exit(1);
    }
    currentSize = 0;				//建立当前大小
};

template <class T, class E>
MinHeap<T, E>::MinHeap(E arr[], int n) {
    maxHeapSize = (DefaultSize < n) ? n : DefaultSize;
    heap = new E[maxHeapSize];
    if (heap == NULL) {
        exit(1);
    }
    for (int i = 0; i < n; i++) heap[i] = arr[i];
    currentSize = n;	       //复制堆数组, 建立当前大小
    int currentPos = (currentSize - 2) / 2;
    //找最初调整位置:最后分支结点
    while (currentPos >= 0) {	    //逐步向上扩大堆
        siftDown(currentPos, currentSize - 1);
        //局部自上向下下滑调整
        currentPos--;
    }
};

template <class T, class E>
void MinHeap<T, E>::siftDown(int start, int m) {
    //私有函数: 从结点start开始到m为止, 自上向下比较, 
    //如果子女的值小于父结点的值,  则关键码小的上浮, 
    //继续向下层比较, 将一个集合局部调整为最小堆。
    int i = start, j = 2 * i + 1;  	//j是i的左子女位置
    E temp = heap[i];
    while (j <= m) {			//检查是否到最后位置
        if (j < m && heap[j] > heap[j + 1]) j++;
        //让j指向两子女中的小者
        if (temp <= heap[j]) break;	//小则不做调整
        else { heap[i] = heap[j];  i = j; j = 2 * j + 1; }
        //否则小者上移, i, j下降
    }
    heap[i] = temp;	      	//回放temp中暂存的元素
};

template <class T, class E>
bool MinHeap<T, E>::Insert(E& x) {
    //公共函数: 将x插入到最小堆中
    if (currentSize == maxHeapSize) 	//堆满
    {
        return false;
    }
    heap[currentSize] = x;  		//插入
    siftUp(currentSize);			//向上调整
    currentSize++;				//堆计数加1
    return true;
};

template <class T, class E>
void MinHeap<T, E>::siftUp(int start) {
    //私有函数: 从结点start开始到结点0为止, 自下向上
    //比较, 如果子女的值小于父结点的值, 则相互交换, 
    //这样将集合重新调整为最小堆。关键码比较符<=
    //在E中定义。
    int j = start, i = (j - 1) / 2;   E temp = heap[j];
    while (j > 0) {		//沿父结点路径向上直达根
        if (heap[i] <= temp) break;							//父结点值小, 不调整
        else { heap[j] = heap[i];  j = i;  i = (i - 1) / 2; }
        //父结点结点值大, 调整
    }
    heap[j] = temp;				//回送
};

template <class T, class E>
bool MinHeap<T, E>::Remove(E& x) {
    if (!currentSize) {		//堆空, 返回false
        return false;
    }
    x = heap[0];
    heap[0] = heap[currentSize - 1];
    currentSize--;
    siftDown(0, currentSize - 1);    	//自上向下调整为堆
    return true;			//返回最小元素
};


int main()
{
    int m;
    scanf("%d", &m);
    MinHeap<double, double> dots(m);
    double a, b, c;
    double temp;
    int count;
    Node* result = NULL;
    Node* tail = NULL;
    while (m > 0) {
        char ch;
        scanf("%c", &ch);
        if (ch == 'A') {
            scanf("%lf", &a);
            scanf("%lf", &b);
            scanf("%lf", &c);
            temp = sqrt(a * a + b * b + c * c);
            //printf("%f\n", temp);
            dots.Insert(temp);
            m--;
        }
        else if (ch == 'Q') {
            scanf("%d", &count);
            int flag = count;
            double total = 0;
            while (flag > 0) {
                dots.Remove(temp);
                total += temp;
                flag--;
            }
            double res = total / count;
            Node* r = new Node(res);
            insertTail(result, tail, r);
            //printf("%.5f\n", res);
            m--;
        }
    }
    Node* s = result;
    while (s != NULL && s->next != NULL) {
        printf("%.5f\n", s->distance);
        s = s->next;
    }
    printf("%.5f", s->distance);
    return 0;
}