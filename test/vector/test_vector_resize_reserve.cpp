// test_vector_resize_reserve.cpp
#include <cassert>
#include <iostream>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

static void dump(const ft::vector<int> &v, const char *tag)
{
    std::cout << tag << " [size=" << v.size() << ", cap=" << v.capacity() << "]: ";
    for (size_t i = 0; i < v.size(); ++i)
        std::cout << v[i] << ' ';
    std::cout << '\n';
}

void test_vector_resize_reserve()
{
    FILE_BANNER();
    print_section("resize / reserve — grow/shrink & invariants");

    ft::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3); // [1,2,3]
    size_t cap0 = v.capacity();
    (void)cap0;

    v.resize(6, 7); // [1,2,3,7,7,7]
    assert(v.size() == 6);
    assert(v[3] == 7 && v[4] == 7 && v[5] == 7);
    assert(v.capacity() >= v.size());
    dump(v, "After resize(6,7)");

    size_t cap_before_shrink = v.capacity();
    v.resize(2); // [1,2]
    assert(v.size() == 2);
    assert(v.capacity() == cap_before_shrink);
    dump(v, "After resize(2)");

    size_t cap_before_bad_reserve = v.capacity();
    v.reserve(1); // no-op
    assert(v.capacity() == cap_before_bad_reserve);

    v.reserve(100);
    size_t cap_reserved = v.capacity();
    assert(cap_reserved >= 100);
    const int *base_after_reserve = &v[0];

    for (int i = 0; i < 50; ++i)
        v.push_back(1000 + i);
    const int *base_after_push = &v[0];
    assert(base_after_reserve == base_after_push);
    dump(v, "After reserve(100) and 50 push_backs");

    size_t cap_before_zero = v.capacity();
    v.resize(0);
    assert(v.size() == 0);
    assert(v.capacity() == cap_before_zero);
    dump(v, "After resize(0)");
}
