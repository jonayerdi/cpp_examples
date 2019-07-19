#include <iostream>
#include <algorithm>

template <class T, class A = std::allocator<T>>
class Vector
{
    private:
        A alloc;
        T *elements;
        size_t capacity;
        size_t count;
    public:
        // Iterator implementation
        class iterator : public std::iterator<std::random_access_iterator_tag, T> { 
        public:
            typedef ptrdiff_t difference_type;
            typedef size_t size_type;
            typedef T value_type;
            typedef T& reference;
            typedef T* pointer;
            typedef std::random_access_iterator_tag iterator_category;

            T *elements;
            size_type index;

            iterator(T *elements, size_type index) {
                this->elements = elements;
                this->index = index;
            }
            iterator(T *elements) : iterator{elements, 0} { }
            iterator(const iterator& iter) {
                elements = iter.elements;
                index = iter.index;
            }
            ~iterator() {}

            // InputIterator
            iterator& operator=(const iterator& iter) {
                elements = iter.elements;
                index = iter.index;
                return *this;
            }
            bool operator==(const iterator& iter) const {
                return index == iter.index;
            }
            bool operator!=(const iterator& iter) const {
                return index != iter.index;
            }
            reference operator*() const {
                return elements[index];
            }
            pointer operator->() const {
                return &elements[index];
            }
            // ForwardIterator
            iterator& operator++() {
                index++;
                return *this;
            }
            // BidirectionalIterator
            iterator& operator--() {
                index--;
                return *this;
            }
            // RandomAccessIterator
            iterator operator+(size_type n) const {
                return iterator {elements, index + n};
            }
            iterator operator-(size_type n) const {
                return iterator {elements, index - n};
            }
            friend iterator operator+(size_type n, const iterator& iter) {
                return iterator {iter.elements, iter.index + n};
            }
            friend iterator operator-(size_type n, const iterator& iter) {
                return iterator {iter.elements, iter.index - n};
            }
            difference_type operator-(iterator iter) const {
                return index - iter.index;
            }
            iterator& operator+=(size_type n) {
                index += n;
                return *this;
            }
            iterator& operator-=(size_type n) {
                index -= n;
                return *this;
            }
            bool operator<(const iterator& iter) const {
                return index < iter.index;
            }
            bool operator>(const iterator& iter) const {
                return index > iter.index;
            }
            bool operator<=(const iterator& iter) const {
                return index <= iter.index;
            }
            bool operator>=(const iterator& iter) const {
                return index >= iter.index;
            }
            reference operator[](size_type idx) const {
                return elements[idx];
            }
        };
        iterator begin() const {
            return iterator {elements, 0};
        }
        iterator end() const {
            return iterator {elements, count};
        }
        // Default constructor
        Vector() {
            capacity = 0;
            count = 0;
            elements = nullptr;
        }
        // Sized constructor
        Vector(size_t initial_capacity) {
            capacity = initial_capacity;
            count = 0;
            elements = alloc.allocate(capacity);
        }
        // Initializer constructor
        Vector(std::initializer_list<T> init) {
            capacity = init.size();
            count = init.size();
            elements = alloc.allocate(capacity);
            std::copy_n(init.begin(), count, this->begin());
        }
        // Copy constructor
        Vector(const Vector<T>& vec) {
            capacity = vec.capacity;
            count = vec.count;
            elements = alloc.allocate(capacity);
            // Does not run assignment operator=
            // memcpy(elements, vec.elements, count * sizeof(T));
            // Should use std::copy_n() instead
            std::copy_n(vec.begin(), count, this->begin());
        }
        // Move constructor
        Vector(Vector<T>&& vec) {
            // Move contents to this instance
            capacity = vec.capacity;
            count = vec.count;
            elements = vec.elements;
            // Wipe old instance just in case
            vec.capacity = 0;
            vec.count = 0;
            vec.elements = nullptr;
        }
        // Destructor
        ~Vector() {
            if(capacity > 0) {
                alloc.deallocate(elements, capacity);
            }
        }
        // Operations
        T& operator[](size_t index) const {
            return elements[index];
        }
        size_t size() {
            return count;
        }
        void push(const T& element) {
            if(count <= capacity) {
                capacity = capacity * 2 + 1;
                if(elements == nullptr) {
                    elements = alloc.allocate(capacity);
                } else {
                    elements = alloc.allocate(capacity, elements);
                }
            }
            elements[count++] = element;
        }
        T pop() {
            return elements[--count];
        }
};

int main() {
    Vector<int> v1 {1,2,3,4,5,6,7,8,9,10,11,12};
    // auto v2 = v1; // Copy assignment
    // auto v2 = std::move(v1); // Move assignment
    //Vector<int> v2 {v1}; // Copy constructor
    Vector<int> v2 {std::move(v1)}; // Move constructor
    for(int e : v2) {
        std::cout << e << std::endl;
    }
    std::cout << v1.size() << std::endl;
}
