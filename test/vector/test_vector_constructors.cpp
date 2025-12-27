// test_vector_constructors.cpp
#include <iostream>
#include <string>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_vector_constructors()
{
    FILE_BANNER();
    print_section("Constructors");

    ft::vector<int> v_default;
    ft::vector<int> v_filled(5, 42);
    int             arr[] = {1, 2, 3, 4};
    ft::vector<int> v_range(arr, arr + 4);
    ft::vector<int> v_copy(v_range);

    std::cout << "v_default.size(): " << v_default.size() << '\n';

    std::cout << "v_filled: ";
    for (size_t i = 0; i < v_filled.size(); ++i)
        std::cout << v_filled[i] << " ";
    std::cout << '\n';

    std::cout << "v_range: ";
    for (size_t i = 0; i < v_range.size(); ++i)
        std::cout << v_range[i] << " ";
    std::cout << '\n';

    std::cout << "v_copy == v_range ? " << (v_copy == v_range ? "true" : "false") << '\n';
}
