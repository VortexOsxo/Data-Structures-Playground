#ifndef LIST_H
#define LIST_H

#include <stdexcept>

template<typename Type>
class List {
public:
    List();
    ~List();

    List(const List &other);
    List &operator=(const List &other);

    List(List &&other) noexcept;
    List &operator=(List &&other) noexcept;

    void push_back(const Type &value);
    void pop_back();

    void push_front(const Type &value);
    void pop_front();

    Type &front();
    const Type &front() const;
    Type &back();
    const Type &back() const;

    Type &at(size_t index);
    const Type &at(size_t index) const;

    void clear();
    [[nodiscard]] size_t size() const;
    [[nodiscard]] bool is_empty() const;

    Type &operator[](size_t index) { return values[index]; }
    const Type &operator[](size_t index) const { return values[index]; }

    template<typename TypeConstness>
    class IteratorTemplate {
    public:
        IteratorTemplate(TypeConstness *data_ptr, size_t index) : data(data_ptr), index(index) {}

        TypeConstness &operator*() const { return data[index]; }
        TypeConstness *operator->() const { return &data[index]; }

        IteratorTemplate &operator++() {
            ++index;
            return *this;
        }

        IteratorTemplate &operator--() {
            --index;
            return *this;
        }

        IteratorTemplate &operator+=(size_t increment) {
            index += increment;
            return *this;
        }

        IteratorTemplate &operator-=(size_t increment) {
            index -= increment;
            return *this;
        }

        bool operator!=(const IteratorTemplate &other) const { return index != other.index; }
        bool operator==(const IteratorTemplate &other) const { return index == other.index; }

    private:
        TypeConstness *data;
        size_t index;
    };

    using Iterator = IteratorTemplate<Type>;
    using ConstIterator = IteratorTemplate<const Type>;

    Iterator begin() { return Iterator(values, 0); }
    Iterator end() { return Iterator(values, _size); }
    ConstIterator begin() const { return ConstIterator(values, 0); }
    ConstIterator end() const { return ConstIterator(values, _size); }
    ConstIterator cbegin() const { return ConstIterator(values, 0); }
    ConstIterator cend() const { return ConstIterator(values, _size); }

private:
    void reallocate(size_t new_capacity);

    Type *values = nullptr;
    size_t capacity = 8;
    size_t _size = 0;
};

template<typename Type>
List<Type>::List() {
    values = new Type[capacity];
}

template<typename Type>
List<Type>::~List() {
    delete[] values;
}

template<typename Type>
List<Type>::List(const List &other) : values(nullptr), capacity(other.capacity), _size(other._size) {
    values = new Type[capacity];
    for (size_t i = 0; i < _size; ++i)
        values[i] = other.values[i];
}

template<typename Type>
List<Type> &List<Type>::operator=(const List &other) {
    if (this == &other)
        return *this;

    if (capacity < other._size) {
        Type *new_values = new Type[other.capacity];
        delete[] values;
        values = new_values;
        capacity = other.capacity;
    }

    _size = other._size;
    for (size_t i = 0; i < _size; ++i)
        values[i] = other.values[i];

    return *this;
}

template<typename Type>
List<Type>::List(List &&other) noexcept : values(other.values), capacity(other.capacity), _size(other._size) {
    other.values = nullptr;
    other.capacity = 0;
    other._size = 0;
}

template<typename Type>
List<Type> &List<Type>::operator=(List &&other) noexcept {
    if (this == &other)
        return *this;

    delete[] values;

    values = other.values;
    capacity = other.capacity;
    _size = other._size;

    other.values = nullptr;
    other.capacity = 0;
    other._size = 0;

    return *this;
}

template<typename Type>
void List<Type>::push_back(const Type &value) {
    if (_size == capacity)
        reallocate(capacity * 2);

    values[_size++] = value;
}

template<typename Type>
void List<Type>::pop_back() {
    if (_size == 0)
        return;

    --_size;
    if (_size <= capacity / 4 && capacity > 8)
        reallocate(capacity / 2);
}

template<typename Type>
void List<Type>::push_front(const Type &value) {
    if (_size == capacity)
        reallocate(capacity * 2);

    for (size_t index = _size; index > 0; --index)
        values[index] = values[index - 1];

    values[0] = value;
    ++_size;
}

template<typename Type>
void List<Type>::pop_front() {
    if (_size == 0)
        return;

    for (size_t index = 0; index < _size - 1; ++index)
        values[index] = values[index + 1];

    --_size;
    if (_size <= capacity / 4 && capacity > 8)
        reallocate(capacity / 2);
}

template<typename Type>
Type &List<Type>::front() {
    if (_size == 0)
        throw std::out_of_range("List is empty");
    return values[0];
}

template<typename Type>
const Type &List<Type>::front() const {
    if (_size == 0)
        throw std::out_of_range("List is empty");
    return values[0];
}

template<typename Type>
Type &List<Type>::back() {
    if (_size == 0)
        throw std::out_of_range("List is empty");
    return values[_size - 1];
}

template<typename Type>
const Type &List<Type>::back() const {
    if (_size == 0)
        throw std::out_of_range("List is empty");
    return values[_size - 1];
}

template<typename Type>
Type &List<Type>::at(size_t index) {
    return const_cast<Type &>(static_cast<const List &>(*this).at(index));
}

template<typename Type>
const Type &List<Type>::at(size_t index) const {
    if (index >= _size)
        throw std::out_of_range("Index out of range");
    return values[index];
}

template<typename Type>
void List<Type>::clear() {
    delete[] values;
    values = new Type[capacity = 8];
    _size = 0;
}

template<typename Type>
size_t List<Type>::size() const {
    return _size;
}

template<typename Type>
bool List<Type>::is_empty() const {
    return _size == 0;
}

template<typename Type>
void List<Type>::reallocate(size_t new_capacity) {
    Type *new_values = new Type[new_capacity];

    for (size_t index = 0; index < _size; ++index)
        new_values[index] = values[index];

    delete[] values;
    values = new_values;
    capacity = new_capacity;
}

#endif // LIST_H
