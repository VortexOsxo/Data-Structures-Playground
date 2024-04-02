cmake_minimum_required(VERSION 3.28)
project(DataStructure CXX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(DataStructure main.cpp
        DataStructure/Array.h
        DataStructure/List.h
        DataStructure/Heap.h
)

add_executable(Tests
        Tests/LinkedListTests.cpp
        Tests/ArrayTests.cpp
        Tests/ListTests.cpp
        Tests/TrackedObject.h
        Tests/HeapTests.cpp
)

target_link_libraries(Tests
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(Tests)
