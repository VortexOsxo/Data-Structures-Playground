#include <gtest/gtest.h>
#include "../DataStructure/LinkedList.h"

TEST(LinkedListTest, PushBackAndFront) {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_front(0);

    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 0);
    EXPECT_EQ(list.back(), 2);
}

TEST(LinkedListTest, PopFront) {
    LinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.pop_front();

    EXPECT_EQ(list.front(), 20);
    EXPECT_EQ(list.size(), 1);
}

TEST(LinkedListTest, EmptyOnConstruction) {
    LinkedList<int> list;
    EXPECT_TRUE(list.is_empty());
    EXPECT_EQ(list.size(), 0);
}

TEST(LinkedListTest, IteratorTraversalAndModification) {
    LinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    int expected = 1;
    for (int value : list) {
        EXPECT_EQ(value, expected);
        expected++;
    }
}

TEST(LinkedListTest, ConstIteratorTraversal) {
    LinkedList<int> list;
    list.push_back(5);
    list.push_back(10);
    list.push_back(15);

    const LinkedList<int>& const_list = list;

    int expected[] = {5, 10, 15};
    int index = 0;

    for (int value: const_list) {
        EXPECT_EQ(value, expected[index++]);
    }

    EXPECT_EQ(index, 3);
}