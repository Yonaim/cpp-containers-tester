#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_stack_basic_performance_smoke()
{
    FILE_BANNER();
    print_section("Performance smoke — push/pop N");

    ft::stack<int> s;
    const int      N = 50000;
    for (int i = 0; i < N; ++i)
        s.push(i);
    for (int i = 0; i < N; ++i)
        s.pop();
    print_bool(s.empty());
}
