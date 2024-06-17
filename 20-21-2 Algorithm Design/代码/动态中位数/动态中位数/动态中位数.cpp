#include <iostream>
using namespace std;
#pragma warning(disable:4996)

#define MAX_HEAP_SIZE 100000

template <class E>
class Heap {
public:
    Heap(int sz);	//构造函数
    ~Heap() { delete[] heap; }	//析构函数
    bool InsertMin(E& d);			//插入
    bool InsertMax(E& d);			//插入
    bool RemoveMin(E& d);			//删除
    bool RemoveMax(E& d);			//删除
    int CurSize() { return currentSize; }
    E getTop() { return heap[0]; }
private:
    E* heap;			//最小堆元素存储数组
    int currentSize;		//最小堆当前元素个数
    int maxHeapSize;	//最小堆最大容量
    void siftDownMin(int start, int m);	//调整算法
    void siftUpMin(int start);		          //调整算法
    void siftDownMax(int start, int m);	//调整算法
    void siftUpMax(int start);		          //调整算法
};

template <class E>
Heap<E>::Heap(int sz) {
    maxHeapSize = sz;
    heap = new E[maxHeapSize];  	//创建堆空间
    currentSize = 0;				//建立当前大小
};

template <class E>
void Heap<E>::siftDownMin(int start, int m) {
    //私有函数: 从结点start开始到m为止, 自上向下比较, 
    //如果子女的值小于父结点的值,  则关键码小的上浮, 
    //继续向下层比较, 将一个集合局部调整为最小堆。
    int i = start, j = 2 * i + 1;  	//j是i的左子女位置
    E temp = heap[i];
    while (j <= m) {			//检查是否到最后位置
        if (j < m && heap[j] > heap[j + 1]) j++;
        //让j指向两子女中的小者
         		if ( temp <= heap[j] ) break;	//小则不做调整
		else { heap[i] = heap[j];  i = j; j = 2*j+1; }
				     	//否则小者上移, i, j下降
	 }
	 heap[i] = temp;	      	//回放temp中暂存的元素
};

template <class E>
void Heap<E>::siftDownMax(int start, int m) {
    //私有函数: 从结点start开始到m为止, 自上向下比较, 
    //如果子女的值小于父结点的值,  则关键码小的上浮, 
    //继续向下层比较, 将一个集合局部调整为最小堆。
    int i = start, j = 2 * i + 1;  	//j是i的左子女位置
    E temp = heap[i];
    while (j <= m) {			//检查是否到最后位置
        if (j < m && heap[j] < heap[j + 1]) j++;
        //让j指向两子女中的小者
        if (temp >= heap[j]) break;	//小则不做调整
        else { heap[i] = heap[j];  i = j; j = 2 * j + 1; }
        //否则小者上移, i, j下降
    }
    heap[i] = temp;	      	//回放temp中暂存的元素
};

template <class E>
bool Heap<E>::InsertMin(E& x) {
    //公共函数: 将x插入到最小堆中
    if (currentSize == maxHeapSize) 	//堆满
    {
        cerr << "Heap Full" << endl;  return false;
    }
    heap[currentSize] = x;  		//插入
    siftUpMin(currentSize);			//向上调整
    currentSize++;				//堆计数加1
    return true;
};

template <class E>
bool Heap<E>::InsertMax(E& x) {
    //公共函数: 将x插入到最小堆中
    if (currentSize == maxHeapSize) 	//堆满
    {
        cerr << "Heap Full" << endl;  return false;
    }
    heap[currentSize] = x;  		//插入
    siftUpMax(currentSize);			//向上调整
    currentSize++;				//堆计数加1
    return true;
};

template <class E>
void Heap<E>::siftUpMin(int start) {
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

template <class E>
void Heap<E>::siftUpMax(int start) {
    //私有函数: 从结点start开始到结点0为止, 自下向上
    //比较, 如果子女的值小于父结点的值, 则相互交换, 
    //这样将集合重新调整为最小堆。关键码比较符<=
    //在E中定义。
    int j = start, i = (j - 1) / 2;   E temp = heap[j];
    while (j > 0) {		//沿父结点路径向上直达根
        if (heap[i] >= temp) break;							//父结点值小, 不调整
        else { heap[j] = heap[i];  j = i;  i = (i - 1) / 2; }
        //父结点结点值大, 调整
    }
    heap[j] = temp;				//回送
};

template <class E>
bool Heap<E>::RemoveMin(E& x) {
    if (!currentSize) {		//堆空, 返回false
        cout << "Heap empty" << endl;  return false;
    }
    x = heap[0];
    heap[0] = heap[currentSize - 1];
    currentSize--;
    siftDownMin(0, currentSize - 1);    	//自上向下调整为堆
    return true;			//返回最小元素
};

template <class E>
bool Heap<E>::RemoveMax(E& x) {
    if (!currentSize) {		//堆空, 返回false
        cout << "Heap empty" << endl;  return false;
    }
    x = heap[0];
    heap[0] = heap[currentSize - 1];
    currentSize--;
    siftDownMax(0, currentSize - 1);    	//自上向下调整为堆
    return true;			//返回最小元素
};

int main()
{
    Heap<int> LeftHeap(MAX_HEAP_SIZE);
    Heap<int> RightHeap(MAX_HEAP_SIZE);
    int temp;
    int current;
    scanf("%d", &temp);
    LeftHeap.InsertMax(temp);
    current = temp;
    printf("%d ", current);
    while (scanf("%d", &temp) == 1) {
        if (temp <= current)
            LeftHeap.InsertMax(temp);
        else
            RightHeap.InsertMin(temp);
        if (LeftHeap.CurSize() > RightHeap.CurSize() + 1) {
            int get;
            LeftHeap.RemoveMax(get);
            RightHeap.InsertMin(get);
            //cout << get << endl;
        }
        else if (LeftHeap.CurSize() < RightHeap.CurSize()) {
            int get;
            RightHeap.RemoveMin(get);
            LeftHeap.InsertMax(get);
            //cout << get << endl;
        }
        current = LeftHeap.getTop();
        printf("%d ", current);
    }   
    return 0;
}