// test_bvector_basic_element_access.cpp
#include <cassert>
#include <iostream>
#include <stdexcept>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_bvector_basic_element_access()
{
    FILE_BANNER();
    print_section("bvector element access (operator[], at, front, back)");

    bool arr[] = {false, true, true, false, true};
    ft::vector<bool> v(arr, arr + 5);

    assert(v[0] == false);
    assert(v[1] == true);

    // operator[] returns proxy; should be assignable
    v[0] = true;
    v[3] = true;
    assert(v[0] == true && v[3] == true);

    // front/back
    assert(static_cast<bool>(v.front()) == true);
    assert(static_cast<bool>(v.back()) == true);

    // at() bounds checking
    assert(v.at(2) == true);
    bool threw = false;
    try
    {
        (void)v.at(999);
    }
    catch (const std::out_of_range &)
    {
        threw = true;
    }
    assert(threw);

    std::cout << "v bits: ";
    for (size_t i = 0; i < v.size(); ++i)
        std::cout << (v[i] ? '1' : '0') << ' ';
    std::cout << '\n';
}
