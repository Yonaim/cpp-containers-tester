// test_bvector_basic_proxy_reference.cpp
#include <cassert>
#include <iostream>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_bvector_basic_proxy_reference()
{
    FILE_BANNER();
    print_section("bvector proxy reference semantics");

    ft::vector<bool> v(8, false);
    v[1] = true;
    v[3] = true;

    // read through proxy
    ft::vector<bool>::reference r1 = v[1];
    bool b1 = r1;
    assert(b1 == true);

    // write through proxy
    r1 = false;
    assert(v[1] == false);

    // reference remains bound to the bit (not to a temporary)
    r1 = true;
    assert((bool)v[1] == true);

    // copy the proxy and assign
    ft::vector<bool>::reference r3 = v[3];
    assert((bool)r3 == true);
    r3 = r1; // assign from another proxy
    assert((bool)v[3] == true);

    // swap bits manually via proxy conversions
    ft::vector<bool>::reference r0 = v[0];
    ft::vector<bool>::reference r7 = v[7];
    r0 = true;
    r7 = false;
    bool tmp = r0;
    r0 = r7;
    r7 = tmp;
    assert((bool)v[0] == false);
    assert((bool)v[7] == true);

    // NOTE: unlike vector<T>, taking the address of v[i] is not supported for vector<bool>.
    // (operator[] returns a proxy, not a real bool&)

    std::cout << "OK\n";
}
