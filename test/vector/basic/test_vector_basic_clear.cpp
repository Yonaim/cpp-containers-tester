// test_vector_basic_clear.cpp
#include <iostream>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_vector_basic_clear()
{
    FILE_BANNER();
    print_section("clear");

    ft::vector<int> v;
    for (int i = 0; i < 6; ++i)
        v.push_back(i);

    std::cout << "Before clear(): size = " << v.size() << ", capacity = " << v.capacity() << '\n';
    v.clear();
    std::cout << "After clear(): size = " << v.size() << ", capacity = " << v.capacity() << '\n';
}
