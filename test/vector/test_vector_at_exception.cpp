// test_vector_at_exception.cpp
#include <iostream>
#include <stdexcept>
#include <string>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_vector_at_exception()
{
    FILE_BANNER();
    print_section("Exception test for at()");

    ft::vector<std::string> v_str(3, "KU");
    try
    {
        v_str.at(10);
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "Caught exception: " << e.what() << '\n';
    }
}
