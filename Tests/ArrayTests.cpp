#include <gtest/gtest.h>
#include "../DataStructure/Array.h"

TEST(ArrayTest, Size) {
    const Array<int, 4> list{};

    EXPECT_EQ(list.size(), 4);
}

TEST(ArrayTest, IteratorBracket) {
    Array<int, 3> list{};
    list[0] = 1;
    list[1] = 4;
    list[2] = 9;

    int index = 1;
    for (int value: list) {
        EXPECT_EQ(value, index*index);
        index++;
    }
}

TEST(ArrayTest, ConstIteratorTraversal) {
    const Array<int, 5> list{10};

    for (int it : list) {
        EXPECT_EQ(it, 10);
    }

    EXPECT_EQ(5, list.size());
}

TEST(ArrayTest, AtMethodValidAccess) {
    Array<int, 3> arr{5};

    EXPECT_EQ(arr.at(0), 5);
    EXPECT_EQ(arr.at(1), 5);
    EXPECT_EQ(arr.at(2), 5);

    arr.at(1) = 10;
    EXPECT_EQ(arr.at(1), 10);
}

TEST(ArrayTest, AtMethodThrowsOutOfRange) {
    Array<int, 3> arr{0};

    EXPECT_THROW(arr.at(-1), std::out_of_range);
    EXPECT_THROW(arr.at(3), std::out_of_range);
    EXPECT_THROW(arr.at(100), std::out_of_range);
}

TEST(ArrayTest, CopyConstructor) {
    Array<int, 4> original{3};
    Array<int, 4> copy(original);

    for (int i : copy) {
        EXPECT_EQ(i, 3);
    }
}

TEST(ArrayTest, CopyAssignment) {
    const Array<int, 4> original{7};
    Array<int, 4> assigned{};
    assigned = original;

    for (int i : assigned) {
        EXPECT_EQ(i, 7);
    }
}