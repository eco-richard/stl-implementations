#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <memory>
#include <stdexcept>

template<typename T>
class myVector {
    std::size_t sizeVar = 0; // Number of elements in vector
    std::size_t capacityVar = 0; // Total current capacity available
    std::unique_ptr<T[]> data = std::make_unique<T[]>(capacityVar);
public:
    // Constructors:
    myVector(); // Default Constructor
    myVector(std::initializer_list<T> elements); // Using initializer list
    myVector(const myVector<T> &rhs); // Copy Constructor
    myVector(myVector<T> &&rhs); // Move constructor
    myVector(std::size_t n, T value); // Copies of specified element
    ~myVector(); // Just to make sure data gets deleted

    // Iterator definition
    class myVector_iterator {
        private:
            T* ptr;
        public:
            myVector_iterator(T* p)
                : ptr(p) {}
            myVector_iterator& operator++() {
                ptr++;
                return *this;
            }
            myVector_iterator operator++(int) {
                myVector_iterator tmp = *this;
                ptr++;
                return tmp;
            }
            myVector_iterator& operator--() {
                ptr--;
                return *this;
            }
            myVector_iterator operator--(int) {
                myVector_iterator tmp = *this;
                ptr--;
                return tmp;
            }
            T& operator[](int index) { return *(ptr + index); }
            T* operator->() { return ptr; }
            T& operator*() { return *ptr; }
            bool operator==(const myVector_iterator &rhs) const {
                return ptr == rhs.ptr;
            }
            bool operator!=(const myVector_iterator &rhs) const {
                return !(*this == rhs);
            }
            myVector_iterator operator+(int i) { return ptr+i; }
            myVector_iterator operator-(int i) { return ptr-i; }
    };

    // Element Access Methods
    T at(std::size_t pos); // Find element at index with bounds checking
    T* front(); // Return pointer to the first element
    T* back(); // Return pointer to the last element

    // Iterators
    myVector_iterator begin() {
        return myVector_iterator(data.get());
    }
    myVector_iterator end() {
        return myVector_iterator(data.get() + int(sizeVar));
    };
    myVector_iterator rbegin() {
        return myVector_iterator(data.get() + int(sizeVar) - 1);
    };
    myVector_iterator rend() {
        return myVector_iterator(data.get() - 1);
    };

    // Capacity Methods
    std::size_t size(); 
    std::size_t capacity();
    bool empty();
    void reserve(std::size_t cap);
    void shrink_to_fit();

    // Modifier Methods
    void clear();
    myVector_iterator insert(myVector_iterator pos, T val);
    myVector_iterator emplace(myVector_iterator pos, T &&val);
    myVector_iterator erase(myVector_iterator pos);
    myVector_iterator erase(myVector_iterator first, myVector_iterator last);
    void push_back(T element);
    void emplace_back(T &&element);
    void pop_back();
    void resize(std::size_t count);

    // Operators 
    myVector<T> &operator=(const myVector<T> rhs); // Copy assignment operator
    myVector<T> &operator=(myVector<T> &&rhs); // Move assignment operator
    T &operator[](std::size_t i) {
        return data[i];
    }
    T* operator&(std::size_t i) { 
        return &data[i];
    }
};

// Default Constructor
template<typename T>
myVector<T>::myVector() : sizeVar(0), capacityVar(0) {}

// Using initializer list
template<typename T>
myVector<T>::myVector(std::initializer_list<T> elements) {
    int counter = 0;
    for (auto x : elements) {
        data[counter] = x;
        counter++;
    }
    sizeVar = counter;
    capacityVar = counter; 
}

// Copy constructor 
template<typename T>
myVector<T>::myVector(const myVector<T> &rhs) {
    sizeVar = rhs.sizeVar;
    capacityVar = rhs.capacityVar;
    for (std::size_t i {0}; i < sizeVar; i++) {
        data[i] = rhs.data[i];
    }
}

// Move constructor
template<typename T>
myVector<T>::myVector(myVector<T> &&rhs) {
    sizeVar = std::move(rhs.sizeVar);
    capacityVar = std::move(rhs.capacityVar);
    data.release();
    data = std::make_unique<T[]>(capacityVar);
    for (std::size_t i {0}; i < sizeVar; i++) {
        data[i] = rhs.data[i];
    }
    rhs.~myVector();
}

template<typename T>
myVector<T>::myVector(std::size_t n, T value) {
    sizeVar = n;
    capacityVar = n;
    for (std::size_t i {0}; i < n; i++) {
        data[i] = value;
    }
}

template<typename T>
myVector<T>::~myVector<T>() { // Just in case
    data.release();
    sizeVar = 0;
    capacityVar = 0;
}

template<typename T>
T myVector<T>::at(std::size_t pos) {
    if (pos > sizeVar) {
        throw std::out_of_range("Larger than this->size()");
    }
    return data[pos];
}

template<typename T>
T* myVector<T>::front() {
    return &data[0];
}

template<typename T>
T* myVector<T>::back() {
    return &data[sizeVar-1];
}

template<typename T>
std::size_t myVector<T>::size() {
    return sizeVar;
}

template<typename T>
std::size_t myVector<T>::capacity() {
    return capacityVar;
}

template<typename T>
bool myVector<T>::empty() {
    if (this->begin() == this->end()) {
        return true;
    }
    return false;
}

template<typename T>
void myVector<T>::reserve(std::size_t cap) {
    capacityVar = cap; 
}

template<typename T>
void myVector<T>::shrink_to_fit() {
    capacityVar = sizeVar;
}

template<typename T>
typename myVector<T>::myVector_iterator myVector<T>::insert(myVector<T>::myVector_iterator pos, T val) {
    sizeVar += 1;
    if (sizeVar > capacityVar) {
        capacityVar = sizeVar;
    }
    std::size_t index = sizeVar - 1;
    for (auto it = this->rbegin(); it != this->rend(); it--) {
        if (it != pos) {
            data[index] = data[index-1];
            --index;
        } else {
            data[index] = val; 
            return it;
        }
    }
    return this->begin()-1;
}

template<typename T>
typename myVector<T>::myVector_iterator myVector<T>::emplace(myVector_iterator pos, T &&val) {
    sizeVar++;
    if (sizeVar > capacityVar) {
        capacityVar = sizeVar;
    }
    std::size_t index {sizeVar - 1};
    for (auto it = this->rbegin(); it != rend(); it--) {
        if (it != pos) {
            data[index] = data[index-1];
            index--;
        } else {
            data[index] = val;
            return it;
        }
    }
    return this->begin()-1;
}

template<typename T>
typename myVector<T>::myVector_iterator myVector<T>::erase(myVector_iterator pos) {
    std::size_t index {0};
    myVector_iterator tmp {nullptr};
    for (auto it = this->begin(); it != pos; it++) {
        index++;
        tmp = it+1;
    }
    for (auto it = pos; it != this->end(); it++) {
        data[index] = data[index+1];
        ++index;
    }
    sizeVar--;
    return tmp;
}

template<typename T>
void myVector<T>::emplace_back(T &&element) {
    sizeVar++;
    if (sizeVar > capacityVar) {
        capacityVar *= 2;
    }
    data[sizeVar - 1] = std::move(element);
}

template<typename T>
void myVector<T>::push_back(T element) {
    sizeVar += 1;
    if (sizeVar > capacityVar) {
        if (capacityVar == 0) {
            capacityVar++;
        } else {
            capacityVar *= 2;
        }
    }
    data[sizeVar-1] = element;
}

template<typename T>
void myVector<T>::pop_back() {
    sizeVar--;
    data[sizeVar].~T();
}

template<typename T>
void myVector<T>::resize(std::size_t count) {
    if (count > sizeVar) {
        // std::size_t tmp = sizeVar;
        // sizeVar = count;
        for (auto i {sizeVar}; i < count; i++) {
            data[i] = 0;
        } 
        sizeVar = count; 
    } else {
        for (auto i {sizeVar}; i <= count; i--) {
            delete &data[i]; 
        }
    }
}

template<typename T>
myVector<T> &myVector<T>::operator=(const myVector<T> rhs) {
    if (this == &rhs) {
        return *this;
    }
    data.release();
    sizeVar = rhs.sizeVar;
    capacityVar = rhs.capacityVar;
    data = std::make_unique<T[]>(capacityVar);
    for (std::size_t i {0}; i < sizeVar; i++) {
        data[i] = rhs.data[i];
    }
    return *this;
}

template<typename T>
myVector<T> &myVector<T>::operator=(myVector<T> &&rhs) {
    if (this == &rhs) {
        return *this;
    }
    data.release();
    sizeVar = rhs.sizeVar;
    capacityVar = rhs.capacityVar;
    data = std::make_unique<T[]>(capacityVar);
    for (std::size_t i {0}; i < sizeVar; i++) {
        data[i] = rhs.data[i];
    }
    rhs.data.release();
    return this;
}

#endif
