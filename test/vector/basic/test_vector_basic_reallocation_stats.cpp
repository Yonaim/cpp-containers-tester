// test_vector_basic_reallocation_stats.cpp
#include <cassert>
#include <iostream>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

static size_t count_reallocations_without_reserve(size_t n)
{
    ft::vector<int> v;
    const int      *base = 0;
    size_t          cnt = 0;
    for (size_t i = 0; i < n; ++i)
    {
        const int *old_base = (v.size() ? &v[0] : 0);
        v.push_back((int)i);
        const int *new_base = &v[0];
        if (old_base && new_base != old_base)
            ++cnt;
        base = new_base;
    }
    (void)base;
    return cnt;
}

static size_t count_reallocations_with_reserve(size_t n)
{
    ft::vector<int> v;
    v.reserve((int)n);
    const int *base = (v.capacity() ? &v[0] : 0);
    size_t     cnt = 0;
    for (size_t i = 0; i < n; ++i)
    {
        const int *old_base = (v.size() ? &v[0] : base);
        v.push_back((int)i);
        const int *new_base = &v[0];
        if (old_base && new_base != old_base)
            ++cnt;
    }
    return cnt;
}

void test_vector_basic_reallocation_stats()
{
    FILE_BANNER();
    print_section("reallocation policy — with vs without reserve");

    const size_t N = 1000;
    size_t       no_res = count_reallocations_without_reserve(N);
    size_t       with_res = count_reallocations_with_reserve(N);

    std::cout << "push_back N=" << N << " | reallocations (no reserve): " << no_res
              << " | (with reserve): " << with_res << '\n';

    assert(with_res == 0);
    assert(no_res >= 1);

    print_section("reallocation policy — OK");
}
