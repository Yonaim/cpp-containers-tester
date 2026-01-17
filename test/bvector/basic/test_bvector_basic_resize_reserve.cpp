// test_bvector_basic_resize_reserve.cpp
#include <cassert>
#include <iostream>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

static void verify_prefix(const ft::vector<bool> &v, size_t n, bool expected)
{
    for (size_t i = 0; i < n; ++i)
        assert((bool)v[i] == expected);
}

void test_bvector_basic_resize_reserve()
{
    FILE_BANNER();
    print_section("bvector resize/reserve");

    ft::vector<bool> v;
    v.resize(5, true);
    assert(v.size() == 5);
    verify_prefix(v, 5, true);

    v.resize(8, false);
    assert(v.size() == 8);
    for (size_t i = 0; i < 5; ++i)
        assert(v[i] == true);
    for (size_t i = 5; i < 8; ++i)
        assert(v[i] == false);

    v.resize(3);
    assert(v.size() == 3);
    verify_prefix(v, 3, true);

    size_t old_cap = v.capacity();
    v.reserve(old_cap + 100);
    assert(v.capacity() >= old_cap + 100);

    // clear should not shrink capacity
    old_cap = v.capacity();
    v.clear();
    assert(v.size() == 0);
    assert(v.capacity() == old_cap);

    std::cout << "reserve+resize ok, cap=" << v.capacity() << "\n";
}
