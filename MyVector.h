#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <cstddef>
#include <exception>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>

template <typename T>
class MyVectorReverseIterator;

// Vector Iterator Definition
template<typename T>
class MyVectorIterator {
 public:
  using ValueType = typename T::ValueType;
  using PointerType = typename T::PointerType;
  using ReferenceType = typename T::ReferenceType;
 public:
  MyVectorIterator(PointerType p) : ptr_(p) {}

  MyVectorIterator& operator++() {
    ptr_++;
    return *this;
  }

  MyVectorIterator operator++(int) {
    MyVectorIterator tmp = *this;
    ptr_++;
    return tmp;
  }

  MyVectorIterator& operator--() {
    ptr_--;
    return *this;
  }

  MyVectorIterator operator--(int) {
    MyVectorIterator tmp = *this;
    ptr_--;
    return tmp;
  }

  ReferenceType operator[](int index) const { return *(ptr_ + index); }

  PointerType operator->() const { return ptr_; }

  ReferenceType operator*() const { return *ptr_; }

  bool operator==(const MyVectorIterator &rhs) {
    return ptr_ == rhs.ptr_;
  }

  bool operator==(const MyVectorReverseIterator<T> &rhs) {
    return ptr_ == rhs.ptr_;
  }

  bool operator!=(const MyVectorIterator &rhs) {
    return !(*this == rhs);
  }

  bool operator!=(const MyVectorReverseIterator<T> &rhs) {
    return !(*this == rhs);
  }

  MyVectorIterator operator+(int i) { return (ptr_ + i); }

  MyVectorIterator operator-(int i) { return (ptr_ - i); }

 private:
  PointerType ptr_;
};

// Vector Iterator Definition
template<typename T>
class MyVectorReverseIterator {
 public:
  using ValueType = typename T::ValueType;
  using PointerType = typename T::PointerType;
  using ReferenceType = typename T::ReferenceType;
 public:
  MyVectorReverseIterator(PointerType p) : ptr_(p) {}

  MyVectorReverseIterator& operator++() {
    ptr_++;
    return *this;
  }

  MyVectorReverseIterator operator++(int) {
    MyVectorReverseIterator tmp = *this;
    ptr_++;
    return tmp;
  }

  MyVectorReverseIterator& operator--() {
    ptr_--;
    return *this;
  }

  MyVectorReverseIterator operator--(int) {
    MyVectorReverseIterator tmp = *this;
    ptr_--;
    return tmp;
  }

  ReferenceType operator[](int index) const { return *(ptr_ + index); }

  PointerType operator->() const { return ptr_; }

  ReferenceType operator*() const { return *ptr_; }

  bool operator==(const MyVectorReverseIterator &rhs) {
    return ptr_ == rhs.ptr_;
  }

  bool operator==(const MyVectorIterator<T> &rhs) {
    return ptr_ == rhs.ptr_;
  }

  bool operator!=(const MyVectorReverseIterator &rhs) {
    return !(*this == rhs);
  }

  bool operator!=(const MyVectorIterator<T> &rhs) {
    return !(*this == rhs);
  }

  MyVectorReverseIterator operator+(int i) { return (ptr_ + i); }

  MyVectorReverseIterator operator-(int i) { return (ptr_ - i); }

 private:
  PointerType ptr_;
};


template<typename T>
class MyVector {
 public:
  using ValueType = T;
  using PointerType = ValueType*;
  using ReferenceType = ValueType&;
  using Iterator = MyVectorIterator<MyVector<T>>;
  using ConstIterator = const MyVectorIterator<MyVector<T>>;
  using ReverseIterator = MyVectorReverseIterator<MyVector<T>>;
  using ConstReverseIterator = const MyVectorReverseIterator<MyVector<T>>;

public:
  // Constructors:
  MyVector() // Default Constuctor
    : size_(0), capacity_(0) {}  // Default Constructor

  MyVector(std::initializer_list<T> elements) { // Using initializer list
    size_ = elements.size();
    capacity_ = elements.size();
    data_ = std::make_unique<ValueType[]>(capacity_);
    int counter {0};
    for (auto x : elements) {
      data_[counter] = std::move(x);
      counter++;
    }
  }

  explicit MyVector(const MyVector<T> &rhs) { // Copy Constructor
    size_ = rhs.size_;
    capacity_ = rhs.capacity_;
    data_ = std::make_unique<ValueType[]>(capacity_);
    for (std::size_t i {0}; i < size_; i++) {
        data_[i] = rhs.data_[i];
    }
  }

  MyVector(MyVector<T> &&rhs) { // Move constructor
    size_ = std::move(rhs.size_);
    capacity_ = std::move(rhs.capacity_);
    data_ = std::move(rhs.data_);
    rhs.~MyVector();
  };

  MyVector(int n) { // Size of vector
    size_ = n;
    capacity_ = n;
  }

  MyVector(std::size_t n, ValueType value) { // Copies of specified element
    size_ = n;
    capacity_ = n;
    for (std::size_t i {0}; i < n; i++) {
        data_[i] = value;
    }
  };

  virtual ~MyVector() { // Just to make sure data_ gets deleted
    data_.reset(nullptr);
    size_ = 0;
    capacity_ = 0;
  }; 

  // Element Access Methods
  ValueType at(std::size_t pos) const { // Find element at index with bounds checking
    if (pos > size_) {
      throw std::out_of_range("Larger than this->size()");
    }
    return data_[pos];
  };
  PointerType front() const { // Return pointer to the first element
    return &data_[0];
  }
  PointerType back() const { // Return pointer to the last element
    return &data_[size_-1];
  }

  // Iterators
  Iterator begin() {
    return Iterator(data_.get());
  }
  ConstIterator cbegin() const {
    return ConstIterator(data_.get());
  }
  Iterator end() {
    return Iterator(data_.get() + int(size_));
  };
  ConstIterator cend() const {
    return ConstIterator(data_.get() + int(size_));
  }
  ReverseIterator rbegin() {
    return ReverseIterator(data_.get() + int(size_) - 1);
  };
  ConstReverseIterator crbegin() const {
    return ConstReverseIterator(data_.get() + int(size_) - 1);
  };
  ReverseIterator rend() {
    return ReverseIterator(data_.get() - 1);
  };
  ConstReverseIterator crend() const {
    return ConstReverseIterator(data_.get() - 1);
  };

  // Capacity Methods
  std::size_t size() const { return size_; }; 

  std::size_t capacity() const { return capacity_; };

  bool empty() const {
    return this->begin() == this->end();
  };

  void reserve(std::size_t cap) {
    if (cap > capacity_) {
      capacity_ = cap;
      std::unique_ptr<ValueType[]> tempBlock = std::make_unique<ValueType[]>(capacity_);
      for (std::size_t i {0}; i < size_; i++) {
        tempBlock[i] = data_[i];
      }
      data_.swap(tempBlock);
    }
  };

  void shrink_to_fit() {
      capacity_ = size_;
  };

  // Modifier Methods
  void clear() {
    for (std::size_t i {0}; i < size_; i++) {
      data_[i].~T();
    }
    size_ = 0;
  };

  ReverseIterator insert(Iterator pos, const ValueType& val) {
    size_++;
    if (capacity_ == 0) { capacity_ = 1; }
    if (size_ > capacity_) {
      int counter {0};
      while (pos != this->begin()) {
        pos--;
        counter++;
      }
      ReAlloc(capacity_ * 2); 
      pos = this->begin()+counter;
    }
    for (auto it {this->rbegin()}; it != this->rend(); it++) {
        if (it != pos) {
          *it = *(it + 1);
        } else {
          *it = val;
          return it;
        }
    }
    return this->rend();
  };

  ReverseIterator insert(Iterator pos, ValueType&& val) {
    size_++;
    if (capacity_ == 0) { capacity_ = 1; }
    if (size_ > capacity_) {
      int counter {0};
      while (pos != this->begin()) {
        pos--;
        counter++;
      }
      ReAlloc(capacity_ * 2); 
      pos = this->begin()+counter;
    }
    for (auto it {this->rbegin()}; it != this->rend(); it++) {
        if (it != pos) {
          *it = *(it + 1);
        } else {
          *it = std::move(val);
          return it;
        }
    }
    return this->rend();
  };

  template <typename ...Args>
  ReverseIterator emplace(Iterator pos, Args&& ...args) {
    return insert(pos, ValueType(std::forward<Args>(args)...));
  }

  Iterator erase(Iterator pos) {
      for (auto it = pos; it != this->end()-1; it++) {
        *it = *(it+1);
      }
      size_--;
      return (pos);
  };

  Iterator erase(Iterator first, Iterator last) {
    auto p1 = first;
    auto p2 = last;
    int elements_removed {1};
    while (p1 != this->end()) {
      if (p2 != this->end()) {
        *p1 = *p2;
        elements_removed++; 
        p1++;
        p2++;
      } else {
        (*p1).~T();
        p1++;
      }
    }
    size_ -= elements_removed;
    return first;
  }

  void push_back(const ValueType &element) {
    size_++;
    if (capacity_ == 0) { capacity_++; }
    if (size_ > capacity_) {
        ReAlloc(capacity_ * 2);
    }
    data_[size_-1] = element;
  };

  void push_back(ValueType&& element) {
    size_++;
    if (capacity_ == 0) {capacity_++;}
    if (size_ > capacity_) {
      ReAlloc(capacity_ * 2);
    }
    data_[size_-1] = std::move(element);
  }

  template <typename ...Args>
  void emplace_back(Args... args) {
    push_back(ValueType(std::forward<Args>(args)...));
  };

  void pop_back() {
    size_--;
    data_[size_].~T();
  };

  void resize(std::size_t count) {
    if (count > size_) {
      std::size_t tmp = size_;
      size_ = count;
      ReAlloc(size_);
      for (std::size_t i {tmp}; i < count; i++) {
        data_[i] = 0;
      }
    } else {
      for (std::size_t i {1}; i < count; i++) {
        this->pop_back();
      }
      size_ = count;
    }
  };

  // Operators 
  MyVector<T> &operator=(const MyVector<T> rhs) { // Copy assignment operator
    if (this == &rhs) {
      return *this;
    }
    data_.reset(nullptr);
    size_ = rhs.size_;
    capacity_ = rhs.capacity_;
    data_ = std::make_unique<ValueType[]>(capacity_);
    for (std::size_t i {0}; i < size_; i++) {
      data_[i] = rhs.data_[i];
    }
    return *this;
  }

  MyVector<T> &operator=(MyVector<T> &&rhs) { // Move assignment operator
    if (this == &rhs) {
      return *this;
    }
    size_ = std::move(rhs.size_);
    capacity_ = std::move(capacity_);
    data_ = std::move(rhs.data_);
    rhs.~MyVector();
    return *this;
  }

  ValueType &operator[](std::size_t i) const {
    return data_[i];
  }

  ValueType &operator[](int i) const {
    return data_[i];
  }

  PointerType operator&(std::size_t i) { 
    return &data_[i];
  }

  friend std::ostream &operator<<(std::ostream &os, const MyVector<T> mv) {
    std::string v_string = "[";
    for (int i {0}; i < mv.size(); i++) {
      if (i == mv.size()-1) {
        v_string += std::to_string(mv[i]) + "]";
      } else {
        v_string += std::to_string(mv[i]) + ", ";
      }
    }
    return os << v_string;
  }

 private:
  std::size_t size_ = 0; // Number of elements in vector
  std::size_t capacity_ = 0; // Total current capacity available
  std::unique_ptr<T[]> data_ = std::make_unique<T[]>(capacity_);
  void ReAlloc(std::size_t new_cap) {
    capacity_ = new_cap;
    std::unique_ptr<ValueType[]> tempBlock = std::make_unique<ValueType[]>(capacity_);
    for (std::size_t i {0}; i < size_-1; i++) {
        tempBlock[i] = std::move(data_[i]);
    }
    data_.swap(tempBlock);
    // tempBlock goes out of scope here and gets garbage collected
  }
};

#endif
