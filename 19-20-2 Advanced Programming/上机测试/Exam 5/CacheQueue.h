#include <stddef.h>

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
            for ( ; q != NULL; ) {
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