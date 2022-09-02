#include <gtest/gtest.h>
#include "myVector.h"
#include <vector>

myVector<int> v1;
std::vector<int> v2;
myVector<int> v3 {1, 2, 3};
std::vector<int> v4 {1, 2, 3};

void emptyVectorTests() {
    ASSERT_EQ(v1.size(), v2.size());
    EXPECT_EQ(v1.capacity(), v2.capacity());
    if (v1.size() > 0) {
        for (std::size_t i {0}; i < v1.size(); i++) {
            EXPECT_EQ(v1[i], v2[i]);
        }
    }
}

void nonemptyVectorTests() {
    ASSERT_EQ(v3.size(), v4.size());
    EXPECT_EQ(v3.capacity(), v4.capacity());
    if (v3.size() > 0) {
        for (std::size_t i {0}; i < v3.size(); i++) {
            EXPECT_EQ(v3[i], v4[i]);
        }
    }
}

TEST(VectorConstructors, DefaultConstructor) {
    myVector<int> dc1;
    std::vector<int> dc2;
    EXPECT_EQ(dc1.size(), dc2.size());
    EXPECT_EQ(dc1.capacity(), dc2.capacity());
}

TEST(VectorConstructors, InitializerList) {
    myVector<int> il1 {1, 2, 3, 4, 5};
    std::vector<int> il2 {1, 2, 3, 4 ,5};
    EXPECT_EQ(il1.size(), il2.size());
    EXPECT_EQ(il1.capacity(), il2.capacity());
    for (std::size_t i {0}; i < il1.size(); i++) {
        EXPECT_EQ(il1[i], il2[i]);
    }
}

TEST(VectorConstructors, CopyConstructor) {
    myVector<int> vec1 {1, 2, 3};
    myVector<int> vec1_copy {vec1};
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
    myVector<int> v1 {1, 2, 3};
    std::vector<int> v2 {1, 2, 3};
    myVector<int> v1_m {std::move(v1)};
    std::vector<int> v2_m {std::move(v2)};
    EXPECT_TRUE(v1.empty()); // myVector should be empty after moving
    EXPECT_EQ(v1_m.size(), v2_m.size());
    EXPECT_EQ(v1_m.capacity(), v2_m.capacity());
    for (std::size_t i {0}; i < v1_m.size(); i++) {
        EXPECT_EQ(v1_m[i], v2_m[i]);
    }
}

TEST(VectorConstructors, SizeElementConstructor) {
    myVector<int> se1 (10, 5);
    std::vector<int> se2 (10, 5);
    EXPECT_EQ(se1.size(), se2.size());
    EXPECT_EQ(se1.capacity(), se2.capacity());
    for (std::size_t i {0}; i < se1.size(); i++) {
        EXPECT_EQ(se1[i], se2[i]);
    }
}

TEST(EmptyVectorTest, VectorSize) {
    EXPECT_EQ(v1.size(), 0);
}

TEST(EmptyVectorTest, VectorCapacity) {
    EXPECT_EQ(v1.capacity(), 0);
}

TEST(EmptyVectorTest, EmptyMethod) {
    EXPECT_TRUE(v1.empty());
    EXPECT_TRUE(v2.empty());
}

TEST(EmptyVectorTest, ReserveMethod) {
    v1.reserve(2);
    v2.reserve(2);
    emptyVectorTests();
}

TEST(EmptyVectorTest, PushBackMethod) {
    v1.push_back(1);
    v2.push_back(1);
    emptyVectorTests();
}

TEST(EmptyVectorTest, PopBackMethod) {
    v1.pop_back();
    v2.pop_back();
    emptyVectorTests();
}

TEST(EmptyVectorTest, ResizeMethod) {
    v1.resize(2);
    v2.resize(2);
}

TEST(NonemptyVectorTest, AtMethod) 
{
    for (std::size_t i {0}; i < v3.size(); i++) {
        EXPECT_EQ(v3.at(i), v4.at(i));
    }
}

TEST(NonemptyVectorTest, NonEmptySize)
{
    EXPECT_EQ(v3.size(), v4.size());
}

TEST(NonemptyVectorTest, ReserveMethod)
{
    v3.reserve(5);
    v4.reserve(5);

    EXPECT_EQ(v3.size(), v4.size());
    EXPECT_EQ(v3.capacity(), v4.capacity());

    for (std::size_t i {0}; i < v3.size(); i++) {
        EXPECT_EQ(v3[i], v4[i]);
    }
}

TEST(NonemptyVectorTest, ShrinkToFitMethod)
{
    v3.shrink_to_fit();
    v4.shrink_to_fit();

    EXPECT_EQ(v3.size(), v4.size());
    EXPECT_EQ(v3.capacity(), v4.capacity());
}

TEST(NonemptyVectorTest, PushBackMethod)
{
    v3.push_back(4);
    v4.push_back(4);
    for (std::size_t i {0}; i < v3.size(); i++) {
        EXPECT_EQ(v3[i], v4[i]);
    }
    // Capacity and size should also still 
    // be equal after push
    EXPECT_EQ(v3.size(), v4.size());
    EXPECT_EQ(v3.capacity(), v4.capacity());
}

TEST(NonemptyVectorTest, PopBackMethod) {
    v3.pop_back();
    v4.pop_back();

    for (std::size_t i {0}; i < v3.size(); i++) {
        EXPECT_EQ(v3[i], v4[i]);
    }
    EXPECT_EQ(v3.size(), v4.size());
    EXPECT_EQ(v3.capacity(), v4.capacity());
}

TEST(NonemptyVectorTest, ResizeMethodGreaterThan) {
    v3.resize(4);
    v4.resize(4);

    for (std::size_t i {0}; i < v3.size(); i++) {
        EXPECT_EQ(v3[i], v4[i]);
    }
}

TEST(NonemptyVectorTest, ResizeMethodLessThan) {
    v3[3] = 4;
    v4[3] = 4;
    v3.push_back(5);
    v4.push_back(5);
    v3.push_back(6);
    v4.push_back(6);

    v3.resize(4);
    v4.resize(4);

    for (std::size_t i {0}; i < v3.size(); i++) {
        EXPECT_EQ(v3[i], v4[i]);
    }
}
