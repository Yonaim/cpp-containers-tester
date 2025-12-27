// test_vector_assignment.cpp
#include <iostream>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_vector_assignment()
{
    FILE_BANNER();
    print_section("Assignment operator");

    ft::vector<int> v_filled(5, 42);
    ft::vector<int> v_assign;
    v_assign = v_filled;

    std::cout << "v_assign.size(): " << v_assign.size() << '\n';
    std::cout << "v_assign[2]: " << v_assign[2] << '\n';
}
