// test_bvector_basic_clear.cpp
#include <cassert>
#include <iostream>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_bvector_basic_clear()
{
    FILE_BANNER();
    print_section("bvector clear/erase destroy semantics (size and contents)");

    ft::vector<bool> v;
    for (int i = 0; i < 16; ++i)
        v.push_back((i % 2) != 0);

    assert(v.size() == 16);
    size_t old_cap = v.capacity();

    v.erase(v.begin() + 3);
    assert(v.size() == 15);
    // verify shape: removed original index 3
    for (size_t i = 0; i < v.size(); ++i)
    {
        bool expected = ((i < 3) ? ((i % 2) != 0) : (((i + 1) % 2) != 0));
        assert((bool)v[i] == expected);
    }

    v.erase(v.begin(), v.begin() + 5);
    assert(v.size() == 10);
    for (size_t i = 0; i < v.size(); ++i)
    {
        bool expected = (((i + 6) % 2) != 0);
        assert((bool)v[i] == expected);
    }

    v.clear();
    assert(v.size() == 0);
    assert(v.empty());
    // capacity is allowed to stay the same (typical behavior)
    assert(v.capacity() == old_cap);
}
