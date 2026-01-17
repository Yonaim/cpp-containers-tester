// test_bvector_basic_comparisons.cpp
#include <cassert>
#include <iostream>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_bvector_basic_comparisons()
{
    FILE_BANNER();
    print_section("bvector comparisons (==, !=, <, <=, >, >=)");

    bool a1[] = {false, true, false, true};
    bool a2[] = {false, true, false, true};
    bool b1[] = {false, true, true};

    ft::vector<bool> a(a1, a1 + 4);
    ft::vector<bool> a_copy(a2, a2 + 4);
    ft::vector<bool> b(b1, b1 + 3);

    assert(a == a_copy);
    assert(!(a != a_copy));

    // lexicographical compare
    assert(b < a);
    assert(b <= a);
    assert(!(b > a));
    assert(!(b >= a));

    // strict inequality by length if prefix equal
    ft::vector<bool> prefix;
    prefix.push_back(false);
    prefix.push_back(true);
    assert(prefix < b);

    std::cout << "OK: comparisons passed\n";
}
