# Data Structures Playground

This is a simple C++ project built to experiment with and understand different **data structures**.  
The main goal is learning, no one should use this code in production.

## What’s Included?

Currently implemented:

- `List<T>` A dynamically resizing array (similar to `std::vector`)
- `Array<T, N>` A fixed-size array with bounds-checked access and iterators
- `LinkedList<T>` A singly linked list for practicing pointer-based structures
- `Heap<T, C>` , Comparator> A binary heap supporting custom comparison via template

## Purpose

This project is a **hands-on learning exercise** focused on building and experimenting with **data structures and
algorithms (DSA)** in modern C++.

It provides a practical way to explore and reinforce key programming concepts:

- Core data structure implementation (e.g., dynamic arrays, lists)
- Time and space complexity trade-offs
- Dynamic memory management
- Iterator design and usage
- Unit testing using **GoogleTest**
- Clean, template-based container design in modern C++

## Testing

This project uses [GoogleTest](https://github.com/google/googletest) to verify correctness.

Tests cover, but not completely:

- Core functionality
- Iterator behavior
- Memory leaks

## Notes

- This is a learning project, some choices prioritize clarity over performance.
- Error handling and edge cases are covered, but not exhaustively.

