#include <iostream>
#include <map>
#include "allocator.h"
#include "container.h"

static constexpr int kSize = 10;

int Factorial(const int number) {
    return number == 0 ? 1 : number * Factorial(number - 1);
}

template <class Allocator>
void UpdateAndPrintMap(const std::string& message, std::map<int, int, std::less<int>, Allocator> map) {
    for (int i = 0; i < kSize; ++i) {
        map[i] = Factorial(i);
    }
    std::cout << message << "{";
    bool first = true;
    for (const auto& [key, value] : map) {
        if (!first) {
            std::cout << ", ";
        }
        first = false;
        std::cout << key << ": " << value;
    }
    std::cout << "}" << std::endl;
}

template <class Allocator>
void UpdateAndPrintList(const std::string& message, otus::List<int, Allocator> list) {
    for (int i = 0; i < kSize; ++i) {
        list.PushBack(i);
    }
    std::cout << message << "{";
    bool first = true;
    for (const int elem : list) {
        if (!first) {
            std::cout << ", ";
        }
        first = false;
        std::cout << elem;
    }
    std::cout << "}" << std::endl;
}

using PairAllocator = otus::Allocator<std::pair<int, int>, kSize>;
using IntAllocator = otus::Allocator<int, kSize>;


int main() {
    UpdateAndPrintMap("std::map with std::allocator:  ", std::map<int, int>{});
    UpdateAndPrintMap("std::map with otus::Allocator: ", std::map<int, int, std::less<int>, PairAllocator>{});

    UpdateAndPrintList("otus::List with std::allocator:  ", otus::List<int>{});
    UpdateAndPrintList("otus::List with otus::Allocator: ", otus::List<int, IntAllocator>{});

    return 0;
}