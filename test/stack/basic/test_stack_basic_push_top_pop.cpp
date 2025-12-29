#include <cassert>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_stack_basic_push_top_pop()
{
    FILE_BANNER();
    print_section("push / top / pop");

    ft::stack<int> s;
    for (int i = 1; i <= 5; ++i)
    {
        s.push(i * 10);
        std::cout << "push(" << i * 10 << ") → top=" << s.top() << ", size=" << s.size() << '\n';
        assert(s.top() == i * 10);
    }

    print_section("After push()");
    print_bool(!s.empty());
    std::cout << "Top element: " << s.top() << '\n';

    int last = s.top();
    s.pop();
    std::cout << "After pop(): top=" << s.top() << ", size=" << s.size() << '\n';
    assert(s.top() != last);
}
