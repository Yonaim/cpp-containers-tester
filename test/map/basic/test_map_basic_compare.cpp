#include <cassert>
#include <iostream>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_map_basic_compare()
{
    FILE_BANNER();
    print_section("key_compare / value_compare / relational operators");

    ft::map<int, std::string> m;
    m.insert(ft::make_pair(10, "Ten"));
    m.insert(ft::make_pair(40, "Forty"));

    ft::map<int, std::string>::key_compare key_comp = m.key_comp();
    std::cout << std::boolalpha;
    std::cout << "key_comp(20,30): " << key_comp(20, 30) << '\n';
    std::cout << "key_comp(30,20): " << key_comp(30, 20) << '\n';

    ft::map<int, std::string>::value_compare val_comp = m.value_comp();
    ft::pair<const int, std::string>         v1(10, "Ten"), v2(40, "Forty");
    std::cout << "val_comp((10,Ten),(40,Forty)): " << val_comp(v1, v2) << '\n';
    std::cout << "val_comp((40,Forty),(10,Ten)): " << val_comp(v2, v1) << '\n';

    ft::map<int, std::string> same(m);
    ft::map<int, std::string> diff(m);
    diff.erase(40);
    diff.insert(ft::make_pair(60, "Sixty"));

    print_bool(m == same);
    assert(m == same);
    print_bool(m != diff);
    assert(m != diff);
    print_bool(m < diff);
    print_bool(diff > m);
    print_bool(m <= same);
    assert(m <= same);
    print_bool(diff >= same);
}
