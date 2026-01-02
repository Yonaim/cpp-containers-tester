// test_vector_basic_push_pop.cpp
#include <cassert>
#include <iostream>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

static void print_vec(const ft::vector<int> &v, const char *label)
{
    std::cout << label << " [size=" << v.size() << "]: ";
    for (size_t i = 0; i < v.size(); ++i)
        std::cout << v[i] << ' ';
    std::cout << '\n';
}

void test_vector_basic_push_pop()
{
    FILE_BANNER();
    print_section("push_back / pop_back — reallocation & stability");

    ft::vector<int> v;
    const int       N = 64;
    size_t          realloc_count = 0;

    for (int i = 0; i < N; ++i)
    {
        const int *old_base = (v.size() ? &v[0] : 0);
        v.push_back(i);
        assert(v.size() == (size_t)(i + 1));
        assert(v.capacity() >= v.size());
        const int *new_base = &v[0];
        if (old_base && new_base != old_base)
            ++realloc_count;
        for (int k = 0; k <= i; ++k)
            assert(v[k] == k);
    }
    print_vec(v, "After bulk push_back");
    std::cout << "Reallocations observed: " << realloc_count << '\n';

    for (int i = N - 1; i >= 0; --i)
    {
        assert(v.back() == i);
        v.pop_back();
        assert(v.size() == (size_t)i);
        if (i > 0)
            assert(!v.empty());
    }
    assert(v.empty());
    print_section("pop_back to empty — OK");

    print_section("push_back without reallocation (reserve pre-capacity)");
    v.reserve(32);
    const int *base_after_reserve = (v.capacity() ? &v[0] : 0);
    for (int i = 0; i < 16; ++i)
        v.push_back(100 + i);
    const int *base_after_push = &v[0];
    if (base_after_reserve)
        assert(base_after_reserve == base_after_push);
    print_vec(v, "After reserved push");
}
