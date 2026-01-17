// test_bvector_basic_push_pop.cpp
#include <cassert>
#include <iostream>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

static bool bit_of(size_t i) { return (i % 3) == 1; }

void test_bvector_basic_push_pop()
{
    FILE_BANNER();
    print_section("bvector push_back/pop_back");

    ft::vector<bool> v;
    size_t cap_changes = 0;
    size_t last_cap = v.capacity();

    for (size_t i = 0; i < 256; ++i)
    {
        v.push_back(bit_of(i));
        if (v.capacity() != last_cap)
        {
            last_cap = v.capacity();
            ++cap_changes;
        }
        assert(v.back() == bit_of(i));
    }

    for (size_t i = 0; i < v.size(); ++i)
        assert(v[i] == bit_of(i));

    // pop half
    for (size_t k = 0; k < 128; ++k)
        v.pop_back();

    assert(v.size() == 128);
    for (size_t i = 0; i < v.size(); ++i)
        assert(v[i] == bit_of(i));

    std::cout << "capacity changed " << cap_changes << " times while pushing 256 bits\n";
    print_section("bvector push/pop OK");
}
