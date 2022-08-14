#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <memory>

template<typename T>
class myVector {
    std::size_t sizeVar;
    std::size_t capacityVar;
    std::unique_ptr<T[]> data = std::make_unique<T[]>(capacityVar);
public:
    // Constructors:
    myVector(); 
    myVector(std::initializer_list<T> elements);
    myVector(const myVector<T> &vec);
    myVector(std::size_t n, T value);
    // ~myVector(); 
    // Element Access Methods
    T at(std::size_t pos);
    T* front();
    T* back();

    // Iterators *Needs a lot of work*
    T* begin();
    T* end();
    T* rbegin();
    T* rend();

    // Capacity Methods
    std::size_t size(); 
    std::size_t capacity();
    bool empty();
    void reserve(std::size_t cap);
    void shrink_to_fit();

    // Modifier Methods
    T* insert(T* pos, T val);
    void push_back(T element);
    void pop_back();
    void resize(std::size_t count);

    // Operators
    /*
    bool operator==(const myVector<T>& l); 
    void operator=(const myVector<T> &vec);
    */
    T &operator[](std::size_t i) {
        if (i > capacityVar) {
            throw std::exception();
        }
        return data[i];
    }
    T* &operator&(std::size_t i) {
        if (i > capacityVar) {
            throw std::exception();
        }
        return &data[i];
    }
};

template<typename T>
myVector<T>::myVector() : sizeVar(0), capacityVar(0) {}

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

template<typename T>
myVector<T>::myVector(const myVector<T> &vec) {
    sizeVar = vec.size();
    capacityVar = vec.capacity();
    for (std::size_t i {0}; i < vec.size(); i++) {
        data[i] = vec[i];
    }
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
T myVector<T>::at(std::size_t pos) {
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
T* myVector<T>::begin() {
    return &data[0];
}

template <typename T>
T* myVector<T>::end() {
    return &data[sizeVar];
}

template<typename T>
T* myVector<T>::rbegin() {
    return &data[sizeVar-1];
}

template<typename T>
T* myVector<T>::rend() {
    return &data[0]-1;
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
T* myVector<T>::insert(T* pos, T val) {
    sizeVar += 1;
    for (auto i = sizeVar-1; i != 0; i--) {
        if (i == *pos) {
            data[i+1] = data[*pos];
            data[*pos] = val;
            return &data[*pos];
        }
        data[i] = data[i-1];
    }
}

template<typename T>
void myVector<T>::push_back(T element) {
    sizeVar += 1;
    if (sizeVar > capacityVar) {
        capacityVar *= 2;
    }
    data[sizeVar-1] = element;
}

template<typename T>
void myVector<T>::pop_back() {
    data[sizeVar-1] = 0;
    sizeVar -= 1;
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
#endif
