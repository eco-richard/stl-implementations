#include <initializer_list>
#include <iostream>
#include <pthread.h>
#include <string>
#include <vector>
using namespace std;

template<typename T>
class myVector {
private:
    size_t size;
    size_t capacity;
    T* data = new T;
public: 
    // Constructors

    myVector() {
        size = 0;
        capacity = 0;
    }
     
    myVector(initializer_list<T> elements) {
        int counter = 0;
        for (auto x : elements) {
            data[counter] = x;
            counter++;
        }
        size = counter;
        capacity = counter;

    }

    // Element Access Methods

    int at(size_t pos) {
        return data[pos]; 
    }

    T* front() {
        return &data[0];
    }

    T* back() {
        return &data[size-1];
    }
    
    // Capacity Methods

    int mySize() {
        return size; 
    }

    int myCapacity() {
        return capacity;
    }

    bool empty() {
        if (myVector::begin() == myVector::end()) {
            return true;
        }
        return false;
    }

    void reserve(size_t cap) {
        capacity = cap;
    }

    void shrinkToFit() {
        capacity = size;
    }

    // Iterators

    T* begin() {return &data[0];}

    T* end() {return &data[size];}

    T* rbegin() {return &data[size-1];}

    T* rend() {return &data[0]-1;}


    // Modifier Methods

    T* insert(size_t pos, T val) {
        data[pos] = val;
        return &data[pos];
    }

    
    void push(T element) {
        size += 1;
        if (size > capacity) {
            capacity *= 2;
        }
        data[size-1] = element;
        
    }

    void pop() {
        data[size-1] = 0;
        size -= 1;
    }
    
    void printVect() {
        cout << "{";
        for (size_t i = 0; i < size; i++) {
            if (i == size-1) {
                cout << data[i] << "}" << endl;
            } else {
                cout << data[i] << ", ";
            }
        }
    }

};

template<typename T>
void getData(myVector<T> *v) {
    v->printVect();
    cout << v->mySize() << endl;
    cout << v->myCapacity() << endl;

}

int main()
{
    myVector<int> *v = new myVector<int>{1, 2, 3};
    v->printVect();
    cout << v->mySize() << endl;
    cout << v->myCapacity() << endl;
    v->push(4);
    getData(v);
    v->push(5);
    v->push(6);
    getData(v);
    v->push(7);
    getData(v);

    v->pop();
    getData(v);

    /*
    myVector<std::string> *strVec = new myVector<std::string>;
    getData(strVec);
    strVec->myPush("hi");
    getData(strVec);

    myVector<double> *vect = new myVector<double>;

    cout << vect->erase() << endl;

    cout << vect->begin() << endl;

    */

    for (auto itr = v->rbegin(); itr != v->rend(); itr--) {
        cout << *itr << endl;
    }

    // getData(v);
    // v->insert(2, 10);
    // getData(v);

    return EXIT_SUCCESS;
}
