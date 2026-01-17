// test_bvector_basic_constructors.cpp
#include <iostream>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

static void dump_bits(const ft::vector<bool> &v, const char *tag)
{
    std::cout << tag << " [size=" << v.size() << "]: ";
    for (size_t i = 0; i < v.size(); ++i)
        std::cout << (v[i] ? '1' : '0') << ' ';
    std::cout << '\n';
}

void test_bvector_basic_constructors()
{
    FILE_BANNER();
    print_section("bvector constructors");

    ft::vector<bool> v0;
    dump_bits(v0, "default");

    ft::vector<bool> v1(8, true);
    dump_bits(v1, "fill (8 x 1)");

    bool             arr[] = {true, false, true, true, false, false};
    ft::vector<bool> v2(arr, arr + sizeof(arr) / sizeof(arr[0]));
    dump_bits(v2, "range ctor");

    ft::vector<bool> v3(v2);
    dump_bits(v3, "copy ctor");

    v3[1] = true;
    v3[2] = false;
    dump_bits(v3, "after bit flips");
}
