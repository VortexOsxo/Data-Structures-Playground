#include <gtest/gtest.h>

#include "../DataStructure/List.h"
#include "TrackedObject.h"

TEST(ListTest, Size) {
    const List<int> list;

    EXPECT_EQ(list.size(), 0);
}

TEST(ListTest, PushBackBracket) {
    List<int> list;
    list.push_back(5);

    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list[0], 5);
}

TEST(ListTest, IsEmpty) {
    List<int> list;
    list.push_back(5);

    EXPECT_FALSE(list.is_empty());
}

TEST(ListTest, PushFrontSingle) {
    List<int> list;
    list.push_front(42);

    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 42);
    EXPECT_EQ(list.back(), 42);
}

TEST(ListTest, PushFrontMultiple) {
    List<int> list;
    list.push_front(10);
    list.push_front(20);
    list.push_front(30);

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 30);
    EXPECT_EQ(list.back(), 10);
}

TEST(ListTest, PopFront) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    list.pop_front();
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 2);
    EXPECT_EQ(list.back(), 3);
}

TEST(ListTest, PopFrontToEmpty) {
    List<int> list;
    list.push_back(5);
    list.pop_front();

    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.size(), 0);
}

TEST(ListTest, PushBackSingle) {
    List<int> list;
    list.push_back(10);

    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.back(), 10);
    EXPECT_EQ(list.front(), 10);
}

TEST(ListTest, PushBackMultiple) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.back(), 3);
    EXPECT_EQ(list.front(), 1);
}

TEST(ListTest, PushBackBeyondInitialCapacity) {
    List<int> list;
    constexpr int count = 100;

    for (int i = 0; i < count; ++i)
        list.push_back(i);

    EXPECT_EQ(list.size(), count);
    EXPECT_EQ(list.back(), 99);
    EXPECT_EQ(list.front(), 0);
}

TEST(ListTest, BackThrowsWhenEmpty) {
    List<int> list;
    EXPECT_THROW(list.back(), std::out_of_range);
}

TEST(ListTest, FrontThrowsWhenEmpty) {
    List<int> list;
    EXPECT_THROW(list.front(), std::out_of_range);
}

TEST(ListTest, AtReturnsCorrectElement) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    EXPECT_EQ(list.at(0), 10);
    EXPECT_EQ(list.at(1), 20);
    EXPECT_EQ(list.at(2), 30);
}

TEST(ListTest, AtThrowsWhenIndexOutOfRange) {
    List<int> list;
    list.push_back(1);

    EXPECT_THROW(list.at(1), std::out_of_range);
    EXPECT_THROW(list.at(100), std::out_of_range);
}

TEST(ListTest, AtReturnsCorrectElementConst) {
    List<int> list;
    list.push_back(42);

    const List<int> &const_list = list;
    EXPECT_EQ(const_list.at(0), 42);
}

TEST(ListMemoryTest, NoMemoryLeaksAfterClear) {
    TrackedObject::reset_counters();

    List<TrackedObject> list;
    for (int i = 0; i < 50; ++i)
        list.push_back(TrackedObject());

    list.clear();

    // Clears keep a default space of 8
    EXPECT_EQ(TrackedObject::created() - 8, TrackedObject::destroyed());
}

TEST(ListMemoryTest, NoMemoryLeaksAfterDestroy) {
    TrackedObject::reset_counters();

    {
        List<TrackedObject> list;
        for (int i = 0; i < 50; ++i)
            list.push_back(TrackedObject());
    }

    EXPECT_EQ(TrackedObject::created(), TrackedObject::destroyed());
}

TEST(ListIteratorTest, IterateThroughElements) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    int expected = 10;
    for (int &it: list) {
        EXPECT_EQ(it, expected);
        expected += 10;
    }
}

TEST(ListIteratorTest, ConstIterateThroughElements) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    const List<int> &const_list = list;
    int expected = 10;
    for (int it: const_list) {
        EXPECT_EQ(it, expected);
        expected += 10;
    }
}
