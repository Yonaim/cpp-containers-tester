// test_bvector_basic_insert_erase.cpp
#include <cassert>
#include <iostream>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

static void show_bits(const ft::vector<bool> &v, const char *tag)
{
    std::cout << tag << " (size=" << v.size() << ", cap=" << v.capacity() << "): ";
    for (size_t i = 0; i < v.size(); ++i)
        std::cout << (v[i] ? '1' : '0') << ' ';
    std::cout << "\n";
}

void test_bvector_basic_insert_erase()
{
    FILE_BANNER();
    print_section("bvector insert/erase");

    ft::vector<bool> v;
    for (int i = 0; i < 8; ++i)
        v.push_back((i % 2) == 0); // 1 0 1 0 1 0 1 0

    show_bits(v, "init");

    // single insert
    v.insert(v.begin() + 2, false); // insert 0
    assert(v.size() == 9);
    assert(v[2] == false);
    show_bits(v, "after insert at 2");

    // insert n copies
    v.insert(v.begin(), 3, true);
    assert(v.size() == 12);
    assert(v[0] == true && v[1] == true && v[2] == true);
    show_bits(v, "after insert n copies at begin");

    // range insert at end
    ft::vector<bool> add;
    add.push_back(true);
    add.push_back(false);
    v.insert(v.end(), add.begin(), add.end());
    assert(v[v.size() - 2] == true && v[v.size() - 1] == false);
    show_bits(v, "after range insert at end");

    // erase single
    ft::vector<bool>::iterator it = v.erase(v.begin());
    assert(v.size() == 13);
    (void)it;
    show_bits(v, "after erase first");

    // erase range
    size_t prev = v.size();
    v.erase(v.begin() + 2, v.begin() + 6);
    assert(v.size() == prev - 4);
    show_bits(v, "after erase range [2,6)");
}
