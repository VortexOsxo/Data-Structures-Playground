#ifndef HEAP_H
#define HEAP_H

#include <stdexcept>

template<typename Type, typename Comparator = std::less<Type>>
class Heap {
public:
    explicit Heap(size_t capacity);
    Heap(size_t capacity, Comparator comparator);
    ~Heap();

    void insert(const Type &value);
    Type &peek() const;
    Type pop();

    [[nodiscard]] bool isEmpty() const { return _size == 0; }
    [[nodiscard]] bool isFull() const { return _size == capacity; }
    [[nodiscard]] size_t size() const { return _size; }

private:
    static size_t left(const size_t position) { return position * 2 + 1; }
    static size_t right(const size_t position) { return position * 2 + 2; }
    static size_t parent(const size_t position) { return (position - 1) / 2; }

    bool compare(size_t a, size_t b) const;
    void swap(size_t a, size_t b);
    void heapify(size_t position = 0);

    Type *values = nullptr;
    size_t _size = 0;
    size_t capacity = 0;
    Comparator comparator;
};

template<typename Type, typename Comparator>
Heap<Type, Comparator>::Heap(size_t capacity) : capacity(capacity) {
    values = new Type[capacity];
}

template<typename Type, typename Comparator>
Heap<Type, Comparator>::Heap(size_t capacity, Comparator comparator) : capacity(capacity), comparator(comparator) {
    values = new Type[capacity];
}

template<typename Type, typename Comparator>
Heap<Type, Comparator>::~Heap() {
    delete[] values;
}

template<typename Type, typename Comparator>
void Heap<Type, Comparator>::insert(const Type &value) {
    if (_size == capacity)
        throw std::overflow_error("Heap is full");

    size_t position = _size++;
    values[position] = value;
    while (position > 0 && compare(position, parent(position))) {
        swap(position, parent(position));
        position = parent(position);
    }
}

template<typename Type, typename Comparator>
Type &Heap<Type, Comparator>::peek() const {
    if (_size == 0)
        throw std::out_of_range("Heap is empty");
    return values[0];
}

template<typename Type, typename Comparator>
Type Heap<Type, Comparator>::pop() {
    if (_size == 0)
        throw std::out_of_range("Heap is empty");

    Type top = values[0];
    values[0] = values[--_size];

    heapify(0);
    return top;
}

template<typename Type, typename Comparator>
bool Heap<Type, Comparator>::compare(size_t a, size_t b) const {
    return comparator(values[a], values[b]);
}

template<typename Type, typename Comparator>
void Heap<Type, Comparator>::swap(size_t a, size_t b) {
    Type temp = values[a];
    values[a] = values[b];
    values[b] = temp;
}

template<typename Type, typename Comparator>
void Heap<Type, Comparator>::heapify(size_t position) {
    while (true) {
        const size_t leftChild = left(position), rightChild = right(position);
        size_t smallest = position;

        if (leftChild < _size && compare(leftChild, smallest))
            smallest = leftChild;
        if (rightChild < _size && compare(rightChild, smallest))
            smallest = rightChild;

        if (smallest != position) {
            swap(position, smallest);
            position = smallest;
        } else {
            break;
        }
    }
}


#endif // HEAP_H
