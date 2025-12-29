#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_stack_basic_comparisons_strict()
{
    FILE_BANNER();
    print_section("Comparisons strict — lexicographical behavior smoke");

    ft::stack<int> a, b;
    a.push(1);
    a.push(2);
    b.push(1);
    b.push(3);
    print_bool(a < b);
}
