// test_bvector_basic_capacity.cpp
#include <cassert>
#include <iostream>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_bvector_basic_capacity()
{
    FILE_BANNER();
    print_section("bvector capacity (size/capacity/reserve/empty)");

    ft::vector<bool> v;
    assert(v.empty());
    assert(v.size() == 0);

    v.reserve(100);
    assert(v.capacity() >= 100);
    std::cout << "After reserve(100): size=" << v.size() << ", cap=" << v.capacity() << '\n';

    for (size_t i = 0; i < 80; ++i)
        v.push_back((i % 3) == 0);

    assert(!v.empty());
    assert(v.size() == 80);
    assert(v.capacity() >= 100); // should not shrink

    const size_t cap_before_clear = v.capacity();
    v.clear();
    assert(v.size() == 0);
    assert(v.capacity() == cap_before_clear);

    print_section("reserve smaller than current capacity should not reduce");
    v.reserve(10);
    assert(v.capacity() == cap_before_clear);
    std::cout << "cap still=" << v.capacity() << '\n';
}
