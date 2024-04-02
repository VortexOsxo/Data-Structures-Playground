#include <gtest/gtest.h>
#include "../DataStructure/Heap.h"

TEST(HeapTest, InsertAndPeek) {
    Heap<int> heap(5);

    heap.insert(5);
    heap.insert(2);
    heap.insert(9);

    EXPECT_EQ(heap.peek(), 2);
    EXPECT_EQ(heap.size(), 3);
}

TEST(HeapTest, InsertAndPopOrder) {
    Heap<int> heap(5);

    heap.insert(7);
    heap.insert(3);
    heap.insert(10);
    heap.insert(1);

    EXPECT_EQ(heap.pop(), 1);
    EXPECT_EQ(heap.pop(), 3);
    EXPECT_EQ(heap.pop(), 7);
    EXPECT_EQ(heap.pop(), 10);
    EXPECT_TRUE(heap.isEmpty());
}

TEST(HeapTest, InsertOverflowThrows) {
    Heap<int> heap(2);
    heap.insert(1);
    heap.insert(2);

    EXPECT_THROW(heap.insert(3), std::overflow_error);
}

TEST(HeapTest, PopOnEmptyThrows) {
    Heap<int> heap(5);
    EXPECT_THROW(heap.pop(), std::out_of_range);
}

TEST(HeapTest, PeekOnEmptyThrows) {
    Heap<int> heap(3);
    EXPECT_THROW(heap.peek(), std::out_of_range);
}

TEST(HeapTest, MaxHeapPopOrder) {
    Heap<int, std::greater<>> heap(5);

    heap.insert(4);
    heap.insert(10);
    heap.insert(1);

    EXPECT_EQ(heap.pop(), 10);
    EXPECT_EQ(heap.pop(), 4);
    EXPECT_EQ(heap.pop(), 1);
}

struct Person {
    std::string name;
    int age{};

    bool operator<(const Person& other) const {
        return age < other.age;
    }
};

TEST(HeapTest, CustomStructMinHeap) {
    Heap<Person> heap(3);

    heap.insert({"Alice", 30});
    heap.insert({"Bob", 25});
    heap.insert({"Charlie", 35});

    EXPECT_EQ(heap.pop().name, "Bob");
    EXPECT_EQ(heap.pop().name, "Alice");
    EXPECT_EQ(heap.pop().name, "Charlie");
}
