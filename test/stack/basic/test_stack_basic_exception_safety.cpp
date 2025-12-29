#include <cassert>
#include <stdexcept>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

struct ThrowOnCopy
{
    int v;
    ThrowOnCopy(int x) : v(x) {}
    ThrowOnCopy(const ThrowOnCopy &other)
    {
        if (other.v == 42)
            throw std::runtime_error("boom");
        v = other.v;
    }
    ThrowOnCopy &operator=(const ThrowOnCopy &other)
    {
        if (other.v == 42)
            throw std::runtime_error("boom");
        v = other.v;
        return *this;
    }
};

void test_stack_basic_exception_safety()
{
    FILE_BANNER();
    print_section("Exception safety (copy throw)");

    ft::stack<ThrowOnCopy> s;
    s.push(ThrowOnCopy(1));
    try
    {
        s.push(ThrowOnCopy(42));
    }
    catch (...)
    {
        std::cout << "caught!\n";
    }
    print_bool(!s.empty());
    std::cout << "top.v=" << s.top().v << '\n';
    assert(s.top().v == 1);
}
