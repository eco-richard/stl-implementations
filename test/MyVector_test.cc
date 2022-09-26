#include <memory>
#include <stdexcept>
#include <vector>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../MyVector.h"

using std::unique_ptr;
using std::make_unique;
using std::vector;
using ::testing::An;

TEST(VectorConstructors, DefaultConstructor) {
  MyVector<int> dc1;
  std::vector<int> dc2;
  EXPECT_EQ(dc1.size(), dc2.size());
  EXPECT_EQ(dc1.capacity(), dc2.capacity());
}

TEST(VectorConstructors, InitializerList) {
  MyVector<int> il1 {1, 2, 3, 4, 5};
  std::vector<int> il2 {1, 2, 3, 4 ,5};
  EXPECT_EQ(il1.size(), il2.size());
  EXPECT_EQ(il1.capacity(), il2.capacity());
  for (std::size_t i {0}; i < il1.size(); i++) {
    EXPECT_EQ(il1[i], il2[i]);
  }
}

TEST(VectorConstructors, CopyConstructor) {
  MyVector<int> vec1 {1, 2, 3};
  MyVector<int> vec1_copy {vec1};
  std::vector<int> vec2 {1, 2, 3};
  std::vector<int> vec2_copy {vec2};
  // vec1 and vec2 should still exist
  EXPECT_TRUE(vec1[0]);
  EXPECT_TRUE(vec2[0]);
  EXPECT_EQ(vec1_copy.size(), vec2_copy.size());
  EXPECT_EQ(vec1_copy.capacity(), vec2_copy.capacity());
  for (std::size_t i {0}; i < vec1_copy.size(); i++) {
    EXPECT_EQ(vec1_copy[i], vec2_copy[i]);
  }
}

TEST(VectorConstructors, MoveConstructor) {
  MyVector<int> v1 {1, 2, 3};
  std::vector<int> v2 {1, 2, 3};
  MyVector<int> v1_m {std::move(v1)};
  std::vector<int> v2_m {std::move(v2)};
  EXPECT_TRUE(v1.empty()); // myVector should be empty after moving
  EXPECT_EQ(v1_m.size(), v2_m.size());
  EXPECT_EQ(v1_m.capacity(), v2_m.capacity());
  for (std::size_t i {0}; i < v1_m.size(); i++) {
    EXPECT_EQ(v1_m[i], v2_m[i]);
  }
}

TEST(VectorConstructors, SizeElementConstructor) {
  MyVector<int> se1 (10, 5);
  std::vector<int> se2 (10, 5);
  EXPECT_EQ(se1.size(), se2.size());
  EXPECT_EQ(se1.capacity(), se2.capacity());
  for (std::size_t i {0}; i < se1.size(); i++) {
    EXPECT_EQ(se1[i], se2[i]);
  }
}

// struct for test fixture to test how empty vectors react
struct EmptyVectorTest : testing::Test {
  unique_ptr<vector<int>> empty_std_v; // Empty Std::vector to run tests on
  unique_ptr<MyVector<int>> empty_my_v; // Empty my vector to do the same

  EmptyVectorTest() {
    empty_std_v = make_unique<std::vector<int>>();
    empty_my_v = make_unique<MyVector<int>>();
  }

  void VectorTest() {
    ASSERT_EQ(empty_std_v->size(), empty_my_v->size());
    EXPECT_EQ(empty_std_v->capacity(), empty_my_v->capacity());
    if (empty_my_v->size() > 0) {
      for (std::size_t i {0}; i < empty_my_v->size(); i++) {
        EXPECT_EQ(empty_std_v->at(i), empty_my_v->at(i));
      }
    }
  }
  virtual ~EmptyVectorTest() {
    empty_std_v.reset(nullptr);
    empty_my_v.reset(nullptr);
  }
};

// Examples struct used for emplace and emplace_back tests
struct Point {
  int x_;
  int y_;

  Point()
  : x_(0), y_(0) {}

  Point(int x, int y)
  : x_(x), y_(y) {}

  Point(const Point &rhs) {
    x_ = rhs.x_;
    y_ = rhs.y_;
  }

  Point(Point &&rhs) {
    x_ = std::move(rhs.x_);
    y_ = std::move(rhs.y_);
  }

  Point& operator=(const Point &rhs) {
    if (*this == rhs) {
      return *this;
    }
    x_ = rhs.x_;
    y_ = rhs.y_;
    return *this;
  }

  Point& operator=(Point&& rhs) {
    if (*this == rhs) {
      return *this;
    }
    x_ = std::move(rhs.x_);
    y_ = std::move(rhs.y_);
    return *this;
  }

  bool operator==(const Point &rhs) const {
    return (x_ == rhs.x_ && y_ == rhs.y_);
  }
};

TEST_F(EmptyVectorTest, VectorSize) {
  EXPECT_EQ(0, empty_my_v->size());
}

TEST_F(EmptyVectorTest, VectorCapacity) {
  EXPECT_EQ(0, empty_my_v->capacity());
}

TEST_F(EmptyVectorTest, EmptyMethod) {
  EXPECT_TRUE(empty_my_v->empty());
  EXPECT_TRUE(empty_std_v->empty());
}

TEST_F(EmptyVectorTest, ReserveMethod) {
  empty_std_v->reserve(5);
  empty_my_v->reserve(5);
  VectorTest();
}

TEST_F(EmptyVectorTest, PushBackMethod) {
  empty_std_v->push_back(1);
  empty_my_v->push_back(1);
  VectorTest();
}

TEST_F(EmptyVectorTest, ResizeMethod) {
  empty_std_v->resize(5);
  empty_my_v->resize(5);
  VectorTest();
};

struct NonEmptyVectorTest : testing::Test {
  unique_ptr<vector<int>> nonempty_std_v;
  unique_ptr<MyVector<int>> nonempty_my_v;

  NonEmptyVectorTest() {
    nonempty_std_v = make_unique<vector<int>>(vector<int>{1, 2, 3, 4, 5});
    nonempty_my_v = make_unique<MyVector<int>>(MyVector<int>{1, 2, 3, 4, 5});
  }

  void VectorTest() {
    ASSERT_EQ(nonempty_std_v->size(), nonempty_my_v->size());
    EXPECT_EQ(nonempty_std_v->capacity(), nonempty_my_v->capacity());
    if (nonempty_my_v->size() > 0) {
      for (std::size_t i {0}; i < nonempty_my_v->size(); i++) {
        EXPECT_EQ(nonempty_std_v->at(i), nonempty_my_v->at(i));
      }
    }
  }

  virtual ~NonEmptyVectorTest() {
    nonempty_std_v.reset(nullptr);
    nonempty_my_v.reset(nullptr);
  }
};

// Test fixture to test nonempty vectors for emplace and emplace_back
struct NonEmptyVectorTestPoint : testing::Test {
  unique_ptr<vector<Point>> nonempty_std_v;
  unique_ptr<MyVector<Point>> nonempty_my_v;

  NonEmptyVectorTestPoint() {
    Point a (1, 2);
    Point b (2, 3);
    Point c (3, 4);
    nonempty_std_v = make_unique<vector<Point>>(vector<Point>{a, b, c});
    nonempty_my_v = make_unique<MyVector<Point>>(MyVector<Point>{a, b, c});
  }

  void VectorTest() {
    ASSERT_EQ(nonempty_std_v->size(), nonempty_my_v->size());
    EXPECT_EQ(nonempty_std_v->capacity(), nonempty_my_v->capacity());
    if (nonempty_my_v->size() > 0) {
      for (std::size_t i {0}; i < nonempty_my_v->size(); i++) {
        EXPECT_EQ(nonempty_std_v->at(i), nonempty_my_v->at(i));
      }
    }
  }

  virtual ~NonEmptyVectorTestPoint() {
    nonempty_std_v.reset(nullptr);
    nonempty_my_v.reset(nullptr);
  }
};

// Test fixture to test empty vectors for emplace and emplace back
struct EmptyVectorTestPoint : testing::Test {
  unique_ptr<vector<Point>> empty_std_v; // Empty Std::vector to run tests on
  unique_ptr<MyVector<Point>> empty_my_v; // Empty my vector to do the same

  EmptyVectorTestPoint() {
    empty_std_v = make_unique<std::vector<Point>>();
    empty_my_v = make_unique<MyVector<Point>>();
  }

  void VectorTest() {
    ASSERT_EQ(empty_std_v->size(), empty_my_v->size());
    EXPECT_EQ(empty_std_v->capacity(), empty_my_v->capacity());
    if (empty_my_v->size() > 0) {
      for (std::size_t i {0}; i < empty_my_v->size(); i++) {
        EXPECT_EQ(empty_std_v->at(i), empty_my_v->at(i));
      }
    }
  }
  virtual ~EmptyVectorTestPoint() {
    empty_std_v.reset(nullptr);
    empty_my_v.reset(nullptr);
  }
};



TEST_F(NonEmptyVectorTest, AtMethod) {
  VectorTest();
};

TEST_F(NonEmptyVectorTest, AtMethodOutOfRange) {
  EXPECT_THROW(nonempty_std_v->at(6), std::out_of_range);
  EXPECT_THROW((nonempty_my_v->at(6)), std::out_of_range);
}

TEST_F(NonEmptyVectorTest, SizeMethod) {
  EXPECT_EQ(nonempty_std_v->size(), nonempty_my_v->size());
}

TEST_F(NonEmptyVectorTest, ReserveMethodLessThanSize) {
  nonempty_std_v->reserve(3);
  nonempty_my_v->reserve(3);
  VectorTest();
}

TEST_F(NonEmptyVectorTest, ReserveMethodGreaterThanSize) {
  nonempty_std_v->reserve(10);
  nonempty_my_v->reserve(10);
  VectorTest();
}

TEST_F(NonEmptyVectorTest, ShrinkToFitMethod) {
  nonempty_std_v->shrink_to_fit();
  nonempty_my_v->shrink_to_fit();
  VectorTest();
}

TEST_F(NonEmptyVectorTest, ClearMethod) {
  nonempty_std_v->clear();
  nonempty_my_v->clear();
  VectorTest();
}

TEST_F(NonEmptyVectorTest, InsertMethod) {
  nonempty_std_v->insert(nonempty_std_v->begin()+1, 10);
  nonempty_my_v->insert(nonempty_my_v->begin()+1, 10);
  VectorTest();
}

TEST_F(NonEmptyVectorTest, EraseMethod) {
  nonempty_std_v->erase(nonempty_std_v->begin()+2);
  nonempty_my_v->erase(nonempty_my_v->begin()+2);
  VectorTest();
}

TEST_F(NonEmptyVectorTest, PushBackMethod) {
  nonempty_std_v->push_back(6);
  nonempty_my_v->push_back(6);
  VectorTest();
}

TEST_F(NonEmptyVectorTest, PopBackMethod) {
  nonempty_std_v->pop_back();
  nonempty_my_v->pop_back();
  VectorTest();
}

TEST_F(NonEmptyVectorTest, ResizeMethodGreaterThanSize) {
  nonempty_std_v->resize(10);
  nonempty_my_v->resize(10);
  VectorTest();
}

TEST_F(NonEmptyVectorTest, ResizeMethodLessThanSize) {
  nonempty_std_v->resize(3);
  nonempty_my_v->resize(3);
  VectorTest();
}

TEST(VectorTest, AccessOperatorOutOfRange) {
  std::vector<int> stdv {1, 2, 3};
  MyVector<int> mv {1, 2, 3}; 
  EXPECT_THAT(stdv[3], An<int>());
  EXPECT_THAT(mv[3], An<int>());
  EXPECT_NO_THROW(stdv[3]);
  EXPECT_NO_THROW(mv[3]);
}

TEST_F(EmptyVectorTestPoint, EmplaceMethod) {
  empty_std_v->emplace(empty_std_v->begin(), 10, 10);
  empty_my_v->emplace(empty_my_v->begin(), 10, 10);
  VectorTest();
}

TEST_F(EmptyVectorTestPoint, EmplaceBackMethod) {
  empty_std_v->emplace_back(10, 10);
  empty_my_v->emplace_back(10, 10);
  VectorTest();
}

TEST_F(NonEmptyVectorTestPoint, EmplaceMethod) {
  nonempty_std_v->emplace(nonempty_std_v->begin()+2, 10, 10);
  nonempty_my_v->emplace(nonempty_my_v->begin()+2, 10, 10);
  VectorTest();
}

TEST_F(NonEmptyVectorTestPoint, EmplaceBackMethod) {
  nonempty_std_v->emplace_back(10, 10);
  nonempty_my_v->emplace_back(10, 10);

  VectorTest();
}
