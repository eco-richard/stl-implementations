#include <gtest/gtest.h>
#include "myVector.h"
#include <vector>

myVector<int> v1;
std::vector<int> v2;
myVector<int> v3 {1, 2, 3};
std::vector<int> v4 {1, 2, 3};


TEST(VectorTest, EmptyVectorSize)
{
    EXPECT_EQ(v1.size(), v2.size());
}

TEST(VectorTest, EmptyVectorCapacity)
{
    EXPECT_EQ(v1.capacity(), v2.capacity());
}

TEST(VectorTest, EqualInitializationList)
{
    for (std::size_t i {0}; i < v3.size(); i++) {
        EXPECT_EQ(v3[i], v4[i]);
    }
}

TEST(VectorTest, AtMethod) 
{
    for (std::size_t i {0}; i < v3.size(); i++) {
        EXPECT_EQ(v3.at(i), v4.at(i));
    }
}

TEST(VectorTest, NonEmptySize)
{
    EXPECT_EQ(v3.size(), v4.size());
}

TEST(VectorTest, NonEmptyCapactiy)
{
    EXPECT_EQ(v3.capacity(), v4.capacity());
}

TEST(VectorTest, EmptyTest) 
{
    // Should return true(1) for empty vectors
    EXPECT_TRUE(v1.empty());
    // Should return false(0) otherwise
    EXPECT_FALSE(v3.empty());
}

TEST(VectorTest, ReserveMethod)
{
    v3.reserve(5);
    v4.reserve(5);

    EXPECT_EQ(v3.size(), v4.size());
    EXPECT_EQ(v3.capacity(), v4.capacity());

    for (std::size_t i {0}; i < v3.size(); i++) {
        EXPECT_EQ(v3[i], v4[i]);
    }
}

TEST(VectorTest, ShrinkToFitMethod)
{
    v3.shrink_to_fit();
    v4.shrink_to_fit();

    EXPECT_EQ(v3.size(), v4.size());
    EXPECT_EQ(v3.capacity(), v4.capacity());
}

TEST(VectorTest, PushBackMethod)
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

TEST(VectorTest, PopBackMethod) {
    v3.pop_back();
    v4.pop_back();

    for (std::size_t i {0}; i < v3.size(); i++) {
        EXPECT_EQ(v3[i], v4[i]);
    }
    EXPECT_EQ(v3.size(), v4.size());
    EXPECT_EQ(v3.capacity(), v4.capacity());
}

TEST(VectorTest, ResizeMethodGreaterThan) {
    v3.resize(4);
    v4.resize(4);

    for (std::size_t i {0}; i < v3.size(); i++) {
        EXPECT_EQ(v3[i], v4[i]);
    }
}

TEST(VectorTest, ResizeMethodLessThan) {
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
