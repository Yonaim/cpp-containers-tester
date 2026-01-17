// test_bvector_basic_iterators.cpp
#include <cassert>
#include <iostream>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_bvector_basic_iterators()
{
    FILE_BANNER();
    print_section("bvector iterators (iterator/const_iterator/reverse)");

    ft::vector<bool> v;
    for (int i = 0; i < 10; ++i)
        v.push_back((i & 1) != 0);

    // iterator traversal
    size_t idx = 0;
    for (ft::vector<bool>::iterator it = v.begin(); it != v.end(); ++it, ++idx)
        assert(bool(*it) == ((idx & 1) != 0));

    // mutate through iterator (proxy)
    for (ft::vector<bool>::iterator it = v.begin(); it != v.end(); ++it)
        *it = !bool(*it);

    for (size_t i = 0; i < v.size(); ++i)
        assert(v[i] == ((i & 1) == 0));

    // const_iterator
    const ft::vector<bool> cv = v;
    idx = 0;
    for (ft::vector<bool>::const_iterator it = cv.begin(); it != cv.end(); ++it, ++idx)
        assert(bool(*it) == ((idx & 1) == 0));

    // reverse_iterator
    ft::vector<bool>::reverse_iterator rit = v.rbegin();
    assert(bool(*rit) == bool(v.back()));

    // distances
    assert(size_t(cv.end() - cv.begin()) == cv.size());

    print_section("bvector iterators OK");
}
