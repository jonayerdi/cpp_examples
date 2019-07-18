#include <iostream>

using namespace std;

template <class T>
struct LinkedListNode
{
    T value;
    LinkedListNode<T> *next;
};

template <class T, class A = allocator<LinkedListNode<T>>>
class LinkedList
{
private:
    A alloc;
    LinkedListNode<T> *head = nullptr;
public:
    LinkedList() {}
    ~LinkedList() {
        while(head != nullptr) {
            auto tmp = head;
            head = head->next;
            alloc.deallocate(tmp,1);
        }
    }
    class iterator { 
    public:
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef T& reference;
        typedef T* pointer;
        typedef std::forward_iterator_tag iterator_category;

        LinkedListNode<T> *ptr = nullptr;

        iterator(LinkedListNode<T> *value) {
            ptr = value;
        }
        iterator() : iterator{nullptr} { }
        iterator(const iterator& iter) {
            ptr = iter.ptr;
        }
        ~iterator() {}

        iterator& operator=(const iterator& iter) {
            ptr = iter.ptr;
        }
        bool operator==(const iterator& iter) const {
            return ptr == iter.ptr;
        }
        bool operator!=(const iterator& iter) const {
            return ptr != iter.ptr;
        }
        iterator& operator++() {
            if(ptr != nullptr) {
                ptr = ptr->next;
            }
            return *this;
        }
        reference operator*() const {
            return ptr->value;
        }
        pointer operator->() const {
            return &ptr->value;
        }
    };
    iterator begin() const {
        return iterator {head};
    }
    iterator end() const {
        return iterator {nullptr};
    }
    iterator find(const T& element) const {
        auto iter = this->begin();
        for(; iter != this->end(); ++iter) {
            if(*iter == element) {
                break;
            }
        }
        return iter;
    }
    iterator append(iterator iter, const T& element) {
        LinkedListNode<T> *node = alloc.allocate(1);
        node->value = element;
        if(iter == this->end()) {
            node->next = this->head;
            this->head = node;
        } else {
            node->next = iter.ptr->next;
            iter.ptr->next = node;
        }
        return iterator {node};
    }
    void append(const T& element) {
        this->append(this->end(), element);
    }
};

int main() {
    LinkedList<int> list {};
    list.append(8);
    list.append(7);
    list.append(6);
    list.append(6);
    list.append(4);
    list.append(6);
    for(auto e : list) {
        cout << e << endl;
    }
    for(auto i : {1,2,3,4,5,6,7,8,9,10}) {
        if(list.find(i) != list.end()) {
            cout << i << " FOUND" << endl;
        } else {
            cout << i << " NOT found" << endl;
        }
    }
}
