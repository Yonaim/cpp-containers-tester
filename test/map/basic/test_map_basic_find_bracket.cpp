#include <cassert>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_map_basic_find_bracket()
{
    FILE_BANNER();
    print_section("find() / operator[] — insertion side-effect");

    ft::map<int, std::string> m;
    m.insert(ft::make_pair(15, "Fifteen"));
    m.insert(ft::make_pair(20, "Twenty"));

    ft::map<int, std::string>::iterator it = m.find(15);
    assert(it != m.end() && it->second == "Fifteen");
    std::cout << "find(15): " << it->first << " => " << it->second << '\n';

    std::cout << "operator[20]: " << m[20] << '\n';
    std::cout << "operator[40]: " << m[40] << '\n';
    assert(m.find(40) != m.end());
    print_tree(m, "After operator[] (insert 40)");
}
