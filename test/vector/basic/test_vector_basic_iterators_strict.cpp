// test_vector_basic_iterators_strict.cpp
#include <cassert>
#include <iostream>
#include <string>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

template <typename It>
static void expect_eq_range(It a, It b, It c, It d)
{
    for (; a != b && c != d; ++a, ++c)
        assert(*a == *c);
    assert((a == b) && (c == d));
}

void test_vector_basic_iterators_strict()
{
    FILE_BANNER();
    print_section("iterators — const, reverse, random-access, diff, bounds");

    ft::vector<std::string> v;
    v.push_back("A");
    v.push_back("B");
    v.push_back("C");
    v.push_back("D");
    ft::vector<std::string>::iterator       it = v.begin();
    ft::vector<std::string>::const_iterator cit = it;
    (void)cit;

    assert(*(v.begin() + 2) == std::string("C"));
    assert(*((v.begin() + 1) + 1) == std::string("C"));
    assert(*(v.end() - 1) == std::string("D"));
    assert((v.begin() + 1) < (v.begin() + 3));
    assert(((v.end() - 1) - v.begin()) == 3);

    std::string fwd, rev;
    for (ft::vector<std::string>::iterator i = v.begin(); i != v.end(); ++i)
        fwd += *i;
    for (ft::vector<std::string>::reverse_iterator r = v.rbegin(); r != v.rend(); ++r)
        rev += *r;
    assert(fwd == "ABCD");
    assert(rev == "DCBA");

    ft::vector<int> vi;
    for (int i = 0; i < 5; ++i)
        vi.push_back(i);
    ft::vector<int>::const_iterator ci = vi.begin();
    int                             sum = 0;
    for (; ci != vi.end(); ++ci)
        sum += *ci;
    assert(sum == 10);

    ft::vector<int>::iterator a = vi.begin();
    ft::vector<int>::iterator b = vi.begin() + 4;
    assert((b - a) == 4);
    assert(*(2 + a) == 2);

    assert(vi.begin() <= vi.end());
    assert(!(vi.end() < vi.begin()));
    ft::vector<int> empty;
    assert(empty.begin() == empty.end());

    ft::vector<int> v2(vi);
    expect_eq_range(vi.begin(), vi.end(), v2.begin(), v2.end());

    print_section("iterators — strict OK");
}
