// test_bvector_basic_assignment.cpp
#include <iostream>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

static void dump_bits(const ft::vector<bool> &v, const char *tag)
{
    std::cout << tag << " [size=" << v.size() << ", cap=" << v.capacity() << "]: ";
    for (size_t i = 0; i < v.size(); ++i)
        std::cout << (v[i] ? '1' : '0') << ' ';
    std::cout << '\n';
}

void test_bvector_basic_assignment()
{
    FILE_BANNER();
    print_section("bvector assignment");

    bool arrA[] = {true, false, true, false, true};
    bool arrB[] = {false, false, true};

    ft::vector<bool> a(arrA, arrA + 5);
    ft::vector<bool> b(arrB, arrB + 3);

    dump_bits(a, "a init");
    dump_bits(b, "b init");

    b = a;
    dump_bits(b, "b = a");

    // flip some bits in b; ensure a unaffected
    b[0] = false;
    b[1] = true;
    dump_bits(a, "a after b modified");
    dump_bits(b, "b after local flips");

    // self assignment
    a = a;
    dump_bits(a, "a = a (self)");

    // assign by range through clear+insert pattern (C++98 compatible)
    ft::vector<bool> c;
    c.insert(c.end(), arrB, arrB + 3);
    dump_bits(c, "c range-insert assigned");
}
