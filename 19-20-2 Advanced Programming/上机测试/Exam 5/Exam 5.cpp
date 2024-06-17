#include <iostream>
#include <stddef.h>
#include <iterator>
using namespace std;

template <typename T, int L>
class Iter; //Iter前置声明以定义CacheQueue中的begin, end迭代器

template <typename T>
struct Node {
    T val;
    Node* next;
};

//模板参数T是数据元素的类型，L是CacheQueue可以包含的元素的最大数量
template <typename T, int L>
class CacheQueue
{
public:
    //类型别名
    using iterator = Iter<T, L>;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    //CacheQueue的默认构造函数
    CacheQueue() {
        size = 0;
        head = NULL;
        tail = NULL;
    }

    //下标访问操作符的重载函数，返回元素的引用
    //下标的顺序由小到大，表示上次使用时间由远及近（即下标为0的元素是最长时间没有使用的元素）
    //例如，队列元素从最久未使用到最近使用的元素依次为2 7 3 4，那么2的偏移量就是0，7的偏移量就是1，依次类推
    reference operator[](size_type idx) {
        Node<value_type>* p = head;
        for (size_type i = 0; i < idx; i++) {
            if (p != NULL)
                p = p->next;
            else
                break;
        }
        if (p == NULL)
            throw std::logic_error("Index overflow.");
        return p->val;
    }

    //使用值为val的元素，如果有多个元素具有相同的值，则本次使用的是最久未被使用过的元素
    void use(value_type val) {
        if (head == NULL)
            return;
        else if (head->val == val) {
            Node<value_type>* p = head;
            head = head->next;
            p->next = NULL;
            tail->next = p;
            tail = p;
        }
        else {
            Node<value_type>* p = head;
            Node<value_type>* q = head->next;
            for (; q != NULL; ) {
                if (q->val == val) {
                    p->next = q->next;
                    q->next = NULL;
                    tail->next = q;
                    tail = q;
                    break;
                }
                else {
                    p = q;
                    q = q->next;
                }
            }
        }
    }

    //向CacheQueue添加元素
    //当CacheQueue已满时，先pop出最长时间没有使用的元素，再加入新的元素
    //返回true表示添加前队列未满，返回false表示添加前队列已满
    bool push(value_type val) {
        if (L == 0)
            return false;
        else if (size == L) {
            Node<value_type>* p = head;
            head = head->next;
            p->next = NULL;
            delete p;
            Node<value_type>* q = new Node<value_type>;
            q->val = val;
            q->next = NULL;
            tail->next = q;
            tail = q;
            return false;
        }
        else if (size == 0) {
            Node<value_type>* q = new Node<value_type>;
            q->val = val;
            q->next = NULL;
            head = q;
            tail = q;
            size += 1;
            return true;
        }
        else {
            Node<value_type>* q = new Node<value_type>;
            q->val = val;
            q->next = NULL;
            tail->next = q;
            tail = q;
            size += 1;
            return true;
        }
    }

    //从CacheQueue取出元素
    //将最长时间没有使用到的元素pop出来
    //返回true表示取出成功，false表示队列调用pop前为空
    bool pop() {
        if (size == 0) {
            return false;
        }
        else {
            Node<value_type>* p = head;
            head = head->next;
            p->next = NULL;
            delete p;
            size -= 1;
            return true;
        }
    }

    //返回迭代器对象begin，即指向最长时间未使用的元素的位置
    iterator begin() {
        return Iter<T, L>(*this, 0);
    }

    //返回迭代器对象end，按照C++标准，end返回的迭代器对象指向最后一个元素的下一个位置，所以容器数据范围实际上是[begin,end)
    iterator end() {
        return Iter<T, L>(*this, size);
    }

protected:
    size_type size;
    Node<value_type>* head;
    Node<value_type>* tail;
    friend class Iter<T, L>;
};

template <typename T, int L>
class Iter
{
public:
    //类型别名，不能删除，否则STL不认为该类属于迭代器
    using container_type = CacheQueue<T, L>;
    using iterator = Iter<T, L>;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::forward_iterator_tag; //前向迭代器标志

    //迭代器的构造函数
    //cq是迭代器对应的容器对象，offset是迭代器指向的容器中元素的位置，即该迭代器指向元素的下标
    Iter(container_type& cq, difference_type offset) : range{ cq }, node{ cq.head } {
        for (size_type i = 0; i < offset; i++) {
            if (node != NULL)
                node = node->next;
            else
                break;
        }
    };

    //重载迭代器操作符

    //判断两个迭代器是否相等，即是否指向了同一个容器的同一个位置
    bool operator==(const iterator& iter) {
        return node == iter.node;
    }
    bool operator!=(const iterator& iter) {
        return node != iter.node;
    }

    //赋值操作符的重载函数，传入指向同一个容器的迭代器，将当前迭代器对象设置为指向与iter相同的位置，返回当前迭代器的引用
    iterator& operator=(const iterator& iter) {
        range = iter.range;
        node = iter.node;
        return *this;
    }

    //间接访问操作符的重载函数，相当于对指针ptr的间接访问操作*ptr，返回迭代器指向容器数据元素的引用
    reference operator*() {
        if (node == NULL)
            throw std::logic_error("Index overflow.");
        return node->val;
    }

    //前置自增运算符的重载函数，先使迭代器指向当前容器元素的下一个位置，再返回迭代器的引用
    iterator& operator++() {
        if (node != NULL) {
            node = node->next;
            return *this;
        }
        else
            return *this;
    }
    //后置自增运算符的重载函数，使迭代器指向当前容器元素的下一个位置，但返回的是递增前的迭代器的拷贝
    iterator operator++(int) {
        if (node != NULL) {
            auto temp = *this;
            node = node->next;
            return temp;
        }
        else
            return *this;
    }

protected:
    container_type& range;
    Node<value_type>* node;
    friend class CacheQueue<T, L>;
};

int main()
{
    /*
    CacheQueue<int, 4> cache_queue;
    cache_queue.push(1);
    cache_queue.push(2);
    cache_queue.push(3);
    cache_queue.push(4);
    cache_queue.use(1);
    cache_queue.pop();
    cache_queue.push(5);
    cache_queue.push(6);
    */

    /*
    CacheQueue<double, 2> cache_queue;
    cache_queue.push(1.1);
    cache_queue.push(2.2);
    cache_queue.push(3.3);
    cache_queue.push(4.4);
    cache_queue[1]=7.7;
    *cache_queue.begin()=1.1;
    */

    /*
    CacheQueue<int, 10> cache_queue;
    cache_queue.push(1);
    cache_queue.push(2);
    cache_queue.push(3);
    cache_queue.push(4);
    cache_queue.push(5);
    Iter<int, 10> iter = cache_queue.begin();
    ++iter;
    iter++;
    while(iter!=cache_queue.end()) {
        cout << *iter << ' ';
        iter++;
    }
    Iter<int,10> second_iter(iter);
    Iter<int,10> third_iter(cache_queue,2);
    third_iter=second_iter;
    */

    return 0;
}