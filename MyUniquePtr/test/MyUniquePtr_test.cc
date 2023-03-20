#include "gmock/gmock.h"
#include <memory>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../UniquePtr.h"

using std::unique_ptr;
using my::UniquePtr; 
using testing::IsNull;
using testing::NotNull;
using testing::An;

TEST(UniquePtrPrimitiveConstructor, DefaultConstructor) {
  unique_ptr<int> std_up;
  UniquePtr<int> my_up;

  EXPECT_THAT(std_up.get(), IsNull()) << "Uninitialized std::unique_ptr should be null";
  EXPECT_THAT(my_up.get(), IsNull()) << "Uninitialized UniquePtr should be null";
}

TEST(UniquePtrPrimitiveConstructor, PointerNoValueConstructor) {
  unique_ptr<int> std_up (new int);
  UniquePtr<int> my_up (new int);

  EXPECT_THAT(*std_up, An<int>()) << "std::unique_ptr should reference an integer";
  EXPECT_THAT(*my_up, An<int>()) << "my UniquePtr should reference an integer";
}

TEST(UniquePtrPrimitiveConstructor, PointerValueConstructor) {
  unique_ptr<int> std_up (new int(10));
  UniquePtr<int> my_up (new int(10));

  EXPECT_THAT(std_up.get(), NotNull());
  EXPECT_THAT(my_up.get(), NotNull());

  EXPECT_EQ(*std_up, 10);
  EXPECT_EQ(*my_up, 10);
}

TEST(UniquePtrPrimitiveConstructor, MoveConstructor) {
  unique_ptr<int> std_tmp (new int(10));
  unique_ptr<int> std_up (std::move(std_tmp));
  UniquePtr<int> my_tmp (new int(10));
  UniquePtr<int> my_up (std::move(my_tmp));

  EXPECT_EQ(*std_up, 10);
  EXPECT_EQ(*my_up, 10);

  EXPECT_THAT(std_tmp.get(), IsNull());
  EXPECT_THAT(my_tmp.get(), IsNull());
}

TEST(UniquePtrPrimitiveConstructor, MoveAssignment) {
  unique_ptr<int> std_tmp (new int(10));
  unique_ptr<int> std_up = std::move(std_tmp);
  UniquePtr<int> my_tmp (new int(10));
  UniquePtr<int> my_up = std::move(my_tmp);

  EXPECT_EQ(*std_up, 10);
  EXPECT_EQ(*my_up, 10);

  EXPECT_THAT(std_tmp.get(), IsNull());
  EXPECT_THAT(my_tmp.get(), IsNull());
}

struct UniquePtrPrimitiveTest : testing::Test {
  unique_ptr<int> std_up = unique_ptr<int>(new int(1));
  UniquePtr<int> my_up = UniquePtr<int>(new int(1));

  void NullTest() {
    EXPECT_THAT(std_up.get(), IsNull());
    EXPECT_THAT(my_up.get(), IsNull());
  }

  void NotNullTest() {
    EXPECT_THAT(std_up.get(), NotNull());
    EXPECT_THAT(my_up.get(), NotNull());
  }

  void ValueTest(int x) {
    EXPECT_EQ(*std_up, x);
    EXPECT_EQ(*my_up, x);
  }

  void PointeeTest(int x) {
    EXPECT_THAT(std_up.get(), testing::Pointee(x));
    EXPECT_THAT(my_up.get(), testing::Pointee(x));
  }
};

TEST_F(UniquePtrPrimitiveTest, ReleaseMethod) {
  int *std_p = std_up.release();
  int *my_p = my_up.release();

  NullTest();
  EXPECT_EQ(*std_p, 1);
  EXPECT_EQ(*my_p, 1);
}

TEST_F(UniquePtrPrimitiveTest, ResetNewPointerMethod) {
  std_up.reset(new int(2));
  my_up.reset(new int(2));

  NotNullTest();
  PointeeTest(2);
}

TEST_F(UniquePtrPrimitiveTest, ResetNullptrMethod) {
  std_up.reset();
  my_up.reset();

  NullTest();
}

TEST_F(UniquePtrPrimitiveTest, SwapMethod) {
  unique_ptr<int> std_swapper (new int(2));
  UniquePtr<int> my_swapper (new int(2));

  std_up.swap(std_swapper);
  my_up.swap(my_swapper);

  NotNullTest();
  PointeeTest(2);

  NotNullTest();
  PointeeTest(2);
}

TEST_F(UniquePtrPrimitiveTest, DereferenceOperator) {
  EXPECT_THAT(*my_up, An<int>());
}

TEST(UniquePtrArrayConstructor, DefaultConstructor) {
  unique_ptr<int[]> std_up;
  UniquePtr<int[]> my_up;

  EXPECT_THAT(std_up.get(), IsNull());
  EXPECT_THAT(my_up.get(), IsNull());
}

TEST(UniquePtrArrayConstructor, PointerSizeConstructor) {
  const int size {5};
  unique_ptr<int[]> std_up (new int[size]);
  UniquePtr<int[]> my_up (new int[size]);

  for (int i {0}; i < size; i++) {
    EXPECT_THAT(std_up[i], testing::An<int>());
    EXPECT_THAT(my_up[i], testing::An<int>());
  }
}

TEST(UniquePtrArrayConstructor, PointerValueConstructor) {
  unique_ptr<int[]> std_up (new int[] {1, 2, 3});
  UniquePtr<int[]> my_up (new int[] {1, 2, 3});

  EXPECT_THAT(std_up.get(), NotNull());
  EXPECT_THAT(my_up.get(), NotNull());

  for (int i {0}; i < 3; i++) {
    EXPECT_EQ(std_up[i], my_up[i]);
  }
}

TEST(UniquePtrArrayConstructor, MoveConstructor) {
  const int size = 3;
  unique_ptr<int[]> std_tmp (new int[size]);
  unique_ptr<int[]> std_up (std::move(std_tmp));
  UniquePtr<int[]> my_tmp (new int[size]);
  UniquePtr<int[]> my_up (std::move(my_tmp));

  for (int i {0}; i < size; i++) {
    EXPECT_THAT(std_up[i], An<int>());
    EXPECT_THAT(std_up[i], An<int>());
  }
}

TEST(UniquePtrArrayConstructor, MoveAssignment) {
  const int size = 3;
  unique_ptr<int[]> std_tmp (new int[size]);
  unique_ptr<int[]> std_up = std::move(std_tmp);
  UniquePtr<int[]> my_tmp (new int[size]);
  UniquePtr<int[]> my_up = std::move(my_tmp);

  for (int i {0}; i < size; i++) {
    EXPECT_THAT(std_up[i], An<int>());
    EXPECT_THAT(std_up[i], An<int>());
  }
}

struct UniquePtrArrayTest : testing::Test {
  const int size = 3;
  unique_ptr<int[]> std_up = unique_ptr<int[]> (new int[size] {1, 2, 3});
  UniquePtr<int[]> my_up = UniquePtr<int[]> (new int[size] {1, 2 ,3});

  void IntegerTest() {
    for (int i {0}; i < size; i++) {
      EXPECT_THAT(std_up[i], An<int>());
      EXPECT_THAT(my_up[i], An<int>());
    }
  }

  void ValueTest(int* x) {
    for (int i {0}; i < size; i++) {
      EXPECT_EQ(std_up[i], x[i]);
      EXPECT_THAT(my_up[i], x[i]);
    }
  }
};

TEST_F(UniquePtrArrayTest, ReleaseMethod) {
  int *std_p = std_up.release();
  int *my_p = my_up.release();

  EXPECT_THAT(std_up.get(), IsNull());
  EXPECT_THAT(my_up.get(), IsNull());

  for (int i {0}; i < size; i++) {
    EXPECT_EQ(std_p[i], i+1);
    EXPECT_EQ(my_p[i], i+1);
  }
}

TEST_F(UniquePtrArrayTest, ResetNewPointerMethod) {
  std_up.reset(new int[] {4, 5, 6});
  my_up.reset(new int[] {4, 5 ,6});

  for (int i {0}; i < size; i++) {
    EXPECT_EQ(std_up[i], i+4);
    EXPECT_EQ(my_up[i], i+4);
  }
}

TEST_F(UniquePtrArrayTest, ResetNullptrMethod) {
  std_up.reset();
  my_up.reset();

  EXPECT_THAT(std_up.get(), IsNull());
  EXPECT_THAT(my_up.get(), IsNull());
}

TEST_F(UniquePtrArrayTest, SwapMethod) {
  const int new_size {4};
  unique_ptr<int[]> std_swapper (new int[new_size] {4, 5, 6, 7});
  UniquePtr<int[]> my_swapper (new int[new_size] {4, 5, 6, 7});

  std_up.swap(std_swapper);
  my_up.swap(my_swapper);

  EXPECT_THAT(std_up.get(), NotNull());
  EXPECT_THAT(my_up.get(), NotNull());

  for (int i {0}; i < size; i++) {
    EXPECT_EQ(std_up[i], i+4);
    EXPECT_EQ(my_up[i], i+4);;
  }
}

TEST(UniquePtrTest, MakeUniquePrimitveTest) {
  UniquePtr<int> up = my::make_unique<int>(10);

  EXPECT_THAT(up.get(), NotNull());
  EXPECT_THAT(up.get(), testing::Pointee(10));
}
// struct to test make_unique
struct Point {
  int x_, y_;

  Point()
  : x_(0), y_(0) {}

  Point(int x, int y)
  : x_(x), y_(y) {}

};

TEST(UniquePtrTest, MakeUniqueObjectTest) {
  UniquePtr<Point> up = my::make_unique<Point>(1, 2);

  EXPECT_THAT(up.get(), NotNull());
  EXPECT_EQ(up->x_, 1);
  EXPECT_EQ(up->y_, 2);
}

TEST(UniquePtrTest, MakeUniqueArrayTest) {
  std::size_t size {3};
  UniquePtr<int[]> up = my::make_unique_array<int[]>(size);

  EXPECT_THAT(up.get(), NotNull());
  for (int i {0}; i < size; i++) {
    EXPECT_THAT(up[i], An<int>());
  }
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest();
  testing::InitGoogleMock();

  return RUN_ALL_TESTS();
}

