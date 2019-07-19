#include <iostream>
#include <exception>
#include <cstring>

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
        class iterator : public std::iterator<std::forward_iterator_tag, T> { 
        public:
            typedef ptrdiff_t difference_type;
            typedef T value_type;
            typedef T& reference;
            typedef T* pointer;
            typedef std::random_access_iterator_tag iterator_category;

            T *elements;
            size_t index;

            iterator(T *elements, size_t index) {
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
            iterator& operator+(size_t n) const {
                return iterator {elements, index + n};
            }
            iterator& operator-(size_t n) const {
                return iterator {elements, index - n};
            }
            iterator& operator+=(size_t n) {
                index += n;
                return *this;
            }
            iterator& operator-=(size_t n) {
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
            reference operator[](size_t idx) const {
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
            size_t i = 0;
            for(T e : init) {
                // Does not run assignment operator=
                memcpy(&elements[i++], &e, sizeof(T));
            }
            // Should use std::copy_n() instead
        }
        // Copy constructor
        Vector(const Vector<T>& vec) {
            capacity = vec.capacity;
            count = vec.count;
            elements = alloc.allocate(capacity);
            // Does not run assignment operator=
            memcpy(elements, vec.elements, count * sizeof(T));
            // Should use std::copy_n() instead
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
    for(int e : v1) {
        std::cout << e << std::endl;
    }
    // auto v2 = v1; // Copy assignment
    // auto v2 = std::move(v1); // Move assignment
    // Vector<int> v2 {v1}; // Copy constructor
    Vector<int> v2 {std::move(v1)}; // Move constructor
    for(int e : v2) {
        std::cout << e << std::endl;
    }
    std::cout << v1.size() << std::endl;
}
