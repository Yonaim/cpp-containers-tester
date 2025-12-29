#include <cassert>
#include <deque>
#include <vector>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_stack_basic_underlying_container()
{
    FILE_BANNER();
    print_section("Underlying container (deque vs vector)");

    ft::stack<int, std::deque<int>>  sd;
    ft::stack<int, std::vector<int>> sv;

    for (int i = 0; i < 3; ++i)
    {
        sd.push(i);
        sv.push(i);
    }
    std::cout << "sd.top=" << sd.top() << ", sv.top=" << sv.top() << '\n';
    assert(sd.top() == sv.top());
}
