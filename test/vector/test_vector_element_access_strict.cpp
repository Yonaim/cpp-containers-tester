// test_vector_element_access_strict.cpp
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_vector_element_access_strict()
{
    FILE_BANNER();
    print_section("element access — const-correctness & exceptions");

    ft::vector<std::string> v;
    v.push_back("A");
    v.push_back("B");
    v.push_back("C");

    v[1] = "BB";
    assert(v[1] == "BB");

    const ft::vector<std::string> &cv = v;
    assert(cv.front() == "A");
    assert(cv.back() == "C");
    assert(cv[0] == "A");

    bool thrown = false;
    try
    {
        (void)v.at(100);
    }
    catch (const std::out_of_range &)
    {
        thrown = true;
    }
    assert(thrown);

    std::string &ref_front = v.front();
    ref_front = "AA";
    assert(v[0] == "AA");

    print_section("element access — strict OK");
}
