#include <iostream>
#include "DataStructure/Array.h"
#include "DataStructure/LinkedList.h"

int main() {

    auto l = LinkedList<int>();

    auto a = Array<int, 5>();

    std::cout << a.size() << std::endl;

    return 0;
}
