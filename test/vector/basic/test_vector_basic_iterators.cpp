// test_vector_basic_iterators.cpp
#include <iostream>
#include <string>
#include "test_config.h"
#include "test_print.h"
#ifdef STD_MODE
    #include <vector>
namespace ft = std;
#else
    #include "vector.h"
#endif

void test_vector_basic_iterators()
{
    FILE_BANNER();
    print_section("Iterators (begin, end, rbegin, rend)");

    ft::vector<std::string> vs;
    vs.push_back("A");
    vs.push_back("B");
    vs.push_back("C");

    std::cout << "Forward iteration: ";
    for (ft::vector<std::string>::iterator it = vs.begin(); it != vs.end(); ++it)
        std::cout << *it << " ";
    std::cout << '\n';

    std::cout << "Reverse iteration: ";
    for (ft::vector<std::string>::reverse_iterator rit = vs.rbegin(); rit != vs.rend(); ++rit)
        std::cout << *rit << " ";
    std::cout << '\n';
}
