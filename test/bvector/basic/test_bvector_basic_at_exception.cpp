// test_bvector_basic_at_exception.cpp
#include <cassert>
#include <iostream>
#include <stdexcept>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_bvector_basic_at_exception()
{
    FILE_BANNER();
    print_section("bvector at() out_of_range");

    ft::vector<bool> v;
    v.push_back(true);
    v.push_back(false);

    bool threw = false;
    try
    {
        (void)v.at(2);
    }
    catch (const std::out_of_range &e)
    {
        threw = true;
        std::cout << "Caught: " << e.what() << "\n";
    }
    assert(threw);

    // in range
    assert(v.at(0) == true);
    assert(v.at(1) == false);

    std::cout << "OK\n";
}
