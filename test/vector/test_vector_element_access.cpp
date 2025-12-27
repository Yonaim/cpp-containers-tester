// test_vector_element_access.cpp
#include <iostream>
#include <string>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_vector_element_access()
{
    FILE_BANNER();
    print_section("Element access");

    ft::vector<std::string> v_str(3, "KU");
    v_str[1] = "CSE";
    v_str.at(2) = "ft_containers";

    std::cout << "front: " << v_str.front() << '\n';
    std::cout << "back:  " << v_str.back() << '\n';
    std::cout << "All elements: ";
    for (size_t i = 0; i < v_str.size(); ++i)
        std::cout << v_str[i] << " ";
    std::cout << '\n';
}
