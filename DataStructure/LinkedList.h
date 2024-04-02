#ifndef LINKEDLIST_H
#define LINKEDLIST_H


template<typename Type>
class LinkedList {
public:
    LinkedList() = default;
    ~LinkedList() noexcept { clear(); }

    LinkedList(const LinkedList &other) = delete;
    LinkedList &operator=(const LinkedList &other) = delete;
    LinkedList(LinkedList &&other) noexcept;
    LinkedList &operator=(LinkedList &&other) noexcept;

private:
    struct Node {
        explicit Node(Type value, Node *next = nullptr) : value(value), next(next) {}
        Type value;
        Node *next = nullptr;
    };

public:
    template<typename TypeConstness>
    struct IteratorTemplate {
        explicit IteratorTemplate(Node *node) : current(node) {}

        TypeConstness &operator*() const { return current->value; }
        TypeConstness *operator->() const { return &(current->value); }

        IteratorTemplate &operator++() {
            current = current->next;
            return *this;
        }

        bool operator==(const IteratorTemplate &other) const { return other.current == current; }
        bool operator!=(const IteratorTemplate &other) const { return other.current != current; }

    private:
        Node *current;

        friend class LinkedList;
    };

    using Iterator = IteratorTemplate<Type>;
    using ConstIterator = IteratorTemplate<const Type>;

    void push_front(Type value);
    void push_back(Type value);

    void pop_front();

    Type &front() { return head->value; }
    const Type &front() const { return head->value; }

    Type &back() { return tail->value; }
    const Type &back() const { return tail->value; }

    void insert_at(const Iterator &iterator, Type value);
    void remove(const Iterator &iterator);

    void clear();

    [[nodiscard]] bool is_empty() const;
    [[nodiscard]] size_t size() const;

    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
    ConstIterator begin() const { return ConstIterator(head); }
    ConstIterator end() const { return ConstIterator(nullptr); }
    ConstIterator cbegin() const { return ConstIterator(head); }
    ConstIterator cend() const { return ConstIterator(nullptr); }

private:
    Node *head = nullptr;
    Node *tail = nullptr;
    size_t _size = 0;
};

template<typename Type>
LinkedList<Type>::LinkedList(LinkedList &&other) noexcept : head(other.head), tail(other.tail), _size(other._size) {
    other.head = other.tail = nullptr;
    other._size = 0;
}

template<typename Type>
LinkedList<Type> &LinkedList<Type>::operator=(LinkedList &&other) noexcept {
    if (this == &other)
        return *this;

    clear();
    head = other.head;
    tail = other.tail;
    _size = other._size;

    other.head = nullptr;
    other.tail = nullptr;
    other._size = 0;

    return *this;
}

template<typename Type>
void LinkedList<Type>::push_front(Type value) {
    auto node = new Node(value, head);
    if (is_empty()) {
        head = tail = node;
    } else {
        head = node;
    }
    _size++;
}

template<typename Type>
void LinkedList<Type>::push_back(Type value) {
    if (is_empty()) {
        tail = head = new Node(value);
    } else {
        tail->next = new Node(value);
        tail = tail->next;
    }
    _size++;
}

template<typename Type>
void LinkedList<Type>::pop_front() {
    if (is_empty())
        return;

    Node *temp = head;
    head = head->next;
    if (head == nullptr)
        tail = nullptr;

    delete temp;
    _size--;
}

template<typename Type>
void LinkedList<Type>::insert_at(const Iterator &iterator, Type value) {
    Node *current = iterator.current;

    Node *new_node = new Node(value, current->next);
    current->next = new_node;

    if (tail == current)
        tail = new_node;
    _size++;
}

template<typename Type>
void LinkedList<Type>::remove(const Iterator &iterator) {
    Node *removed = iterator.current;

    if (removed == head) {
        pop_front();
        return;
    }

    Node *current = head;
    while (current != nullptr) {
        if (current.next != removed) {
            current = current->next;
        }

        current.next = removed->next;
        delete removed;
        --size;
        return;
    }
}

template<typename Type>
void LinkedList<Type>::clear() {
    Node *current = head;

    while (current != nullptr) {
        Node *temp = current;
        current = current->next;
        delete temp;
    }

    head = nullptr;
    tail = nullptr;
    _size = 0;
}

template<typename Type>
bool LinkedList<Type>::is_empty() const {
    return head == nullptr;
}

template<typename Type>
size_t LinkedList<Type>::size() const {
    return _size;
}


#endif // LINKEDLIST_H
