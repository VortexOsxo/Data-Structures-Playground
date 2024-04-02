#ifndef ARRAY_H
#define ARRAY_H

template<typename Type, size_t size_temp>
class Array {
public:
    Array() = default;
    explicit Array(Type default_value);
    ~Array() = default;

    Array(const Array &other);
    Array &operator=(const Array &other);
    Array(Array &&other) noexcept = default;
    Array &operator=(Array &&other) noexcept = default;

    [[nodiscard]] constexpr size_t size() const { return size_temp; }

    Type &operator[](size_t index) { return values[index]; }
    const Type &operator[](size_t index) const { return values[index]; }

    Type &at(size_t index);
    const Type &at(size_t index) const;

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
    Iterator end() { return Iterator(values, size_temp); }
    ConstIterator begin() const { return ConstIterator(values, 0); }
    ConstIterator end() const { return ConstIterator(values, size_temp); }
    ConstIterator cbegin() const { return ConstIterator(values, 0); }
    ConstIterator cend() const { return ConstIterator(values, size_temp); }

private:
    Type values[size_temp];
};

template<typename Type, size_t size_temp>
Array<Type, size_temp>::Array(Type default_value) {
    for (size_t index = 0; index < size_temp; ++index) {
        values[index] = default_value;
    }
}

template<typename Type, size_t size_temp>
Array<Type, size_temp>::Array(const Array &other) {
    for (size_t index = 0; index < size_temp; ++index) {
        values[index] = other[index];
    }
}

template<typename Type, size_t size_temp>
Array<Type, size_temp> &Array<Type, size_temp>::operator=(const Array &other) {
    if (this == &other)
        return *this;

    for (size_t index = 0; index < size_temp; ++index) {
        values[index] = other[index];
    }
    return *this;
}

template<typename Type, size_t size_temp>
Type &Array<Type, size_temp>::at(size_t index) {
    return const_cast<Type &>(static_cast<const Array &>(*this).at(index));
}

template<typename Type, size_t size_temp>
const Type &Array<Type, size_temp>::at(size_t index) const {
    if (index >= size_temp) {
        throw std::out_of_range("Array index out of range");
    }
    return values[index];
}

#endif // ARRAY_H
