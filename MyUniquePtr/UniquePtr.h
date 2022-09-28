/*
   My implementation of the STL's std::unique_ptr
*/

#include <memory>
#include <iostream>
#include <ostream>

namespace my {

template <typename T>
struct default_delete {
  default_delete() = default;

  template <typename U>
  default_delete(const default_delete<U>& d) {
    *this = static_cast<T*>(d);
  }

  void operator()(T* ptr) const {
    delete ptr;
  }
};

template<typename T, typename Deleter = my::default_delete<T>> /* Will make my own default delete later */
class UniquePtr {
 public:
  using ValueType = T;
  using PointerType = ValueType*;

 public:
  /* Constructors */

  /* Default Constructor: assigns ptr to nullptr */
  UniquePtr()
    : ptr_(nullptr) {
    }

  /* Creates a UniquePointer based on raw pointer */
  explicit UniquePtr(PointerType p)
    : ptr_(p) {
    }

  UniquePtr(PointerType p, Deleter d)
    : ptr_(p), deleter_(d) {
    }

  /* Move constructor: transfers ownership to newly created pointer */
  UniquePtr(UniquePtr &&u) {
    ptr_ = std::move(u.get());
    deleter_ = std::move(u.get_deleter());
    u = nullptr;
  };  
  
  /* Move assignment operator: transfers ownership using '=' */
  UniquePtr &operator=(UniquePtr &&u) {
    if (*this == u) {
      return *this;
    }
    ptr_ = std::move(u.get());
    deleter_ = std::move(u.get_deleter());
    u = nullptr;
    return *this;
  }

  /* Destructor */ 
  ~UniquePtr() {
    if (ptr_ != nullptr) {
      get_deleter()(ptr_);
    }
  };
 
  /* Modifiers */

  PointerType release() {
    PointerType p = ptr_;
    ptr_ = nullptr;
    return p;
  };

  void reset(PointerType p = PointerType()) {
    PointerType tmp = ptr_;
    ptr_ = p;
    if (tmp) {
      get_deleter()(tmp);
    }
  };

  void swap(UniquePtr &other) {
    std::swap(ptr_, other.ptr_);
    std::swap(deleter_, other.deleter_);
  };

  /* Observers */

  PointerType get() const {
    return ptr_;
  };

  Deleter& get_deleter() const {
    return deleter_;
  };

  Deleter& get_deleter() {
    return deleter_;
  }

  explicit operator bool() const {
    return !(ptr_ == nullptr);
  };

  ValueType operator*() const {
    return *ptr_;
  }

  PointerType operator->() const {
    return ptr_;
  };

  /* Comparison operators */

  UniquePtr &operator=(std::nullptr_t) {
    ptr_ = nullptr;
    return *this;
  }

  bool operator==(const UniquePtr &rhs) {
    return (ptr_ == rhs.ptr_);
  };

  bool operator!=(const UniquePtr &rhs) {
    return !(*this == rhs);
  };

  bool operator<(const UniquePtr &rhs) {
    return ptr_ < rhs.ptr_;
  };

  bool operator<=(const UniquePtr &rhs) {
    return !(*this > rhs);
  };

  bool operator>(const UniquePtr &rhs) {
    return ptr_ > rhs.ptr_;
  };

  bool operator>=(const UniquePtr &rhs) {
    return !(*this > rhs);
  };

  /* Output stream operator */
  friend std::ostream& operator<<(std::ostream &os, const UniquePtr &ptr) {
    return os << ptr;
  }

private:
  PointerType ptr_ = nullptr;
  Deleter deleter_;
};

template <typename T, typename... Args>
UniquePtr<T> make_unique(Args&&... args) {
  UniquePtr<T> up (new T(std::forward<Args>(args)...));
  return up;
}

template <typename T>
struct default_delete<T[]> {
  default_delete() = default;

  template <typename U>
  default_delete (const default_delete<U[]> &d) {
    *this = dynamic_cast<T[]>(d); 
  }

  template <typename U>
  void operator()(U* ptr) const {
    // static_assert(ptr, "Incomplete Type: Array of unknown bound.\n");
    delete [] ptr; 
  }
};

// Unique ptr for array types
template <typename T, typename Deleter>
class UniquePtr<T[], Deleter> {
 public:
  using ValueType = T;
  using PointerType = ValueType*;

 public:
  /* Constructors */

  /* Default Constructor */
  UniquePtr()
    :ptr_(nullptr) {}

  /* Creates based on raw pointer */
  template <typename U>
  explicit UniquePtr(U p)
    : ptr_(p) {} 

  template <typename U>
  explicit UniquePtr(U p, Deleter d)
    : ptr_(p), deleter_(d) {}

  /* Move constructor */
  UniquePtr(UniquePtr&& u) {
    ptr_ = std::move(u.get());
    deleter_ = std::move(u.get_deleter());
    u = nullptr;
  }

  /* Move assignment operator */
  UniquePtr &operator=(UniquePtr&&u) {
    if (*this == u) {
      return *this;
    }
    ptr_ = std::move(u.get());
    deleter_ = std::move(u.get_deleter());
    u = nullptr;
    return *this;
  }

  ~UniquePtr() {
    if (ptr_ != nullptr) {
      get_deleter()(ptr_);
    }
  }

  /* Modifiers */

  PointerType release() {
    PointerType p = ptr_;
    ptr_ = nullptr;
    return p;
  }

  void reset(PointerType p = PointerType()) {
    PointerType tmp = ptr_;
    ptr_ = p;
    if (tmp) {
      get_deleter()(tmp);
    }
  }

  void swap(UniquePtr &other) {
    std::swap(ptr_, other.ptr_);
    std::swap(deleter_, other.deleter_);
  }

  /* Observers */

  PointerType get() const {
    return ptr_;
  }

  Deleter& get_deleter() const {
    return deleter_;
  }

  Deleter& get_deleter() {
    return deleter_;
  }

  explicit operator bool() const {
    return ptr_ != nullptr;
  }

  ValueType& operator[](std::size_t i) const {
    return ptr_[i];
  }

  ValueType& operator[](int i) {
    return ptr_[i];
  }

  /* Comparison Operators */

  UniquePtr &operator=(std::nullptr_t) {
    ptr_ = nullptr;
    return *this;
  }

  bool operator==(const UniquePtr &rhs) {
    return (ptr_ == rhs.ptr_);
  };

  bool operator!=(const UniquePtr &rhs) {
    return !(*this == rhs);
  };

  bool operator<(const UniquePtr &rhs) {
    return ptr_ < rhs.ptr_;
  };

  bool operator<=(const UniquePtr &rhs) {
    return !(*this > rhs);
  };

  bool operator>(const UniquePtr &rhs) {
    return ptr_ > rhs.ptr_;
  };

  bool operator>=(const UniquePtr &rhs) {
    return !(*this > rhs);
  };

  friend std::ostream& operator<<(std::ostream &os, const UniquePtr &ptr) {
    return os << ptr;
  }

 private:
  PointerType ptr_ = nullptr;
  Deleter deleter_ = my::default_delete<T[]>();
};

template <typename T>
UniquePtr<T> make_unique_array(std::size_t size) {
  UniquePtr<T> up (new std::remove_extent_t<T>[size]);
  return up;
}

} // Namespace bracket
