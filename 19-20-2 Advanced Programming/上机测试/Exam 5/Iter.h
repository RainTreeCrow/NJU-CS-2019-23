#include <stddef.h>
#include <iterator>

template <typename T>
struct Node;

template <typename T, int L>
class CacheQueue;

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