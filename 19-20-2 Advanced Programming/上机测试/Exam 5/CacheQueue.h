#include <stddef.h>

template <typename T, int L>
class Iter; //Iterǰ�������Զ���CacheQueue�е�begin, end������

template <typename T>
struct Node {
    T val;
    Node* next;
};

//ģ�����T������Ԫ�ص����ͣ�L��CacheQueue���԰�����Ԫ�ص��������
template <typename T, int L>
class CacheQueue
{
public:
    //���ͱ���
    using iterator = Iter<T, L>;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    //CacheQueue��Ĭ�Ϲ��캯��
    CacheQueue() {
        size = 0;
        head = NULL;
        tail = NULL;
    }

    //�±���ʲ����������غ���������Ԫ�ص�����
    //�±��˳����С���󣬱�ʾ�ϴ�ʹ��ʱ����Զ���������±�Ϊ0��Ԫ�����ʱ��û��ʹ�õ�Ԫ�أ�
    //���磬����Ԫ�ش����δʹ�õ����ʹ�õ�Ԫ������Ϊ2 7 3 4����ô2��ƫ��������0��7��ƫ��������1����������
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

    //ʹ��ֵΪval��Ԫ�أ�����ж��Ԫ�ؾ�����ͬ��ֵ���򱾴�ʹ�õ������δ��ʹ�ù���Ԫ��
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

    //��CacheQueue���Ԫ��
    //��CacheQueue����ʱ����pop���ʱ��û��ʹ�õ�Ԫ�أ��ټ����µ�Ԫ��
    //����true��ʾ���ǰ����δ��������false��ʾ���ǰ��������
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

    //��CacheQueueȡ��Ԫ��
    //���ʱ��û��ʹ�õ���Ԫ��pop����
    //����true��ʾȡ���ɹ���false��ʾ���е���popǰΪ��
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

    //���ص���������begin����ָ���ʱ��δʹ�õ�Ԫ�ص�λ��
    iterator begin() {
        return Iter<T, L>(*this, 0);
    }

    //���ص���������end������C++��׼��end���صĵ���������ָ�����һ��Ԫ�ص���һ��λ�ã������������ݷ�Χʵ������[begin,end)
    iterator end() {
        return Iter<T, L>(*this, size);
    }

protected:
    size_type size;
    Node<value_type>* head;
    Node<value_type>* tail;
    friend class Iter<T, L>;
};