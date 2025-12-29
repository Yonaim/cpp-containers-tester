#include <cassert>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_stack_basic_comparisons()
{
    FILE_BANNER();
    print_section("Comparison operators (==, !=, <, <=, >, >=)");

    ft::stack<int> s1, s2;
    for (int i = 0; i < 3; ++i)
    {
        s1.push(i);
        s2.push(i);
    }

    print_bool(s1 == s2);
    assert(s1 == s2);
    s2.push(99);
    print_bool(s1 != s2);
    assert(s1 != s2);
    print_bool(s1 < s2);
    print_bool(s2 > s1);
    print_bool(s1 <= s2);
    print_bool(s2 >= s1);
}
