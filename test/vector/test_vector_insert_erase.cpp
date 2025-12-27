// test_vector_insert_erase.cpp
#include <cassert>
#include <iostream>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

static void show(const ft::vector<int> &v, const char *title)
{
    std::cout << title << " [size=" << v.size() << ", cap=" << v.capacity() << "]: ";
    for (size_t i = 0; i < v.size(); ++i)
        std::cout << v[i] << ' ';
    std::cout << '\n';
}

void test_vector_insert_erase()
{
    FILE_BANNER();
    print_section("insert / erase — single, fill, range, boundaries");

    ft::vector<int> v;
    for (int i = 1; i <= 5; ++i)
        v.push_back(i); // [1,2,3,4,5]
    show(v, "Init");

    ft::vector<int>::iterator it = v.insert(v.begin() + 1, 99); // [1,99,2,3,4,5]
    assert(*it == 99);
    assert(v[1] == 99 && v.size() == 6);
    show(v, "After single insert at index 1");

    v.insert(v.begin(), 3, 77); // [77,77,77,1,99,2,3,4,5]
    assert(v.size() == 9);
    assert(v[0] == 77 && v[1] == 77 && v[2] == 77);
    show(v, "After fill insert at begin (3 x 77)");

    ft::vector<int> add;
    add.push_back(-1);
    add.push_back(-2);                         // [-1,-2]
    v.insert(v.end(), add.begin(), add.end()); // ...,-1,-2
    assert(v[v.size() - 1] == -2 && v[v.size() - 2] == -1);
    show(v, "After range insert at end");

    int removed_val = v[4];
    v.erase(v.begin() + 4);
    show(v, "After erase single at index 4");
    assert(v[4] != removed_val);

    v.erase(v.begin(), v.begin() + 3);
    show(v, "After erase range [0,3)");

    ft::vector<int>::iterator it_end_before = v.end();
    (void)it_end_before;
    v.insert(v.end(), 555);
    ft::vector<int>::iterator it_new = v.end() - 1;
    assert(*it_new == 555);
    show(v, "After insert at end() (== push_back)");

    ft::vector<int> copy_v(v);
    v.insert(v.begin() + 1, copy_v.begin() + 1, copy_v.begin() + 3);
    show(v, "After safe self-like range insert (via copy)");
}
