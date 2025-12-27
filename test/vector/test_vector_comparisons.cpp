// test_vector_comparisons.cpp
#include <iostream>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_vector_comparisons()
{
    FILE_BANNER();
    print_section("Comparison operators (==, !=, <, <=, >, >=)");

    ft::vector<int> v1(3, 10);
    ft::vector<int> v2(3, 10);
    ft::vector<int> v3(3, 20);
    ft::vector<int> v4(2, 10);

    print_bool(v1 == v2); // true
    print_bool(v1 != v3); // true
    print_bool(v1 < v3);  // true
    print_bool(v3 > v1);  // true
    print_bool(v4 <= v1); // true
    print_bool(v3 >= v2); // true
}
