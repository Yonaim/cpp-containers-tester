#include <cassert>
#include <string>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_map_basic_iterators_basic()
{
    FILE_BANNER();
    print_section("Iterators — basic forward (begin/end), const-correctness");

    ft::map<int, std::string> m;
    int                       ks[] = {20, 10, 30, 5, 15};
    const char               *vs[] = {"20", "10", "30", "5", "15"};
    for (int i = 0; i < 5; ++i)
        m.insert(ft::make_pair(ks[i], vs[i]));

    std::string order;
    for (ft::map<int, std::string>::iterator it = m.begin(); it != m.end(); ++it)
        order += it->second + std::string(" ");
    std::cout << order << '\n';

    const ft::map<int, std::string> &cm = m;
    for (ft::map<int, std::string>::const_iterator cit = cm.begin(); cit != cm.end(); ++cit)
    {
        std::cout << cit->first << ":" << cit->second << " ";
    }
    std::cout << '\n';
}
