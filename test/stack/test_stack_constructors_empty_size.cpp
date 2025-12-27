#include <cassert>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_stack_constructors_empty_size()
{
    FILE_BANNER();
    print_section("Constructor / empty / size");

    ft::stack<int> s;
    print_bool(s.empty());
    std::cout << "Initial size: " << s.size() << '\n';
    assert(s.empty() && s.size() == 0);

    s.push(1);
    s.push(2);
    ft::stack<int> cpy(s); // copy-ctor
    ft::stack<int> asn;
    asn = s; // copy-assign
    std::cout << "cpy.size=" << cpy.size() << ", asn.size=" << asn.size() << '\n';
    assert(cpy.size() == s.size() && asn.size() == s.size());
}
