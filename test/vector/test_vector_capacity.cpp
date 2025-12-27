// test_vector_capacity.cpp
#include <iostream>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_vector_capacity()
{
    FILE_BANNER();
    print_section("Capacity test");

    ft::vector<int> v_default;
    ft::vector<int> v_filled(5, 42);

    std::cout << "v_filled.size():     " << v_filled.size() << '\n';
    std::cout << "v_filled.capacity(): " << v_filled.capacity() << '\n';
    std::cout << "v_filled.max_size(): " << v_filled.max_size() << '\n';
    std::cout << "v_default.empty():   " << v_default.empty() << '\n';
}
