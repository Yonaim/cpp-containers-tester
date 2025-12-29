#include <cassert>
#include <string>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_stack_basic_types_strings()
{
    FILE_BANNER();
    print_section("Stack of strings");

    ft::stack<std::string> s;
    s.push("Konkuk");
    s.push("University");
    s.push("CSE");

    std::cout << "Top: " << s.top() << '\n';
    assert(s.top() == "CSE");
    s.pop();
    std::cout << "After pop(): top=" << s.top() << ", size=" << s.size() << '\n';
    assert(s.top() == "University");
}
