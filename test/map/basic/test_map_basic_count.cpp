#include <cassert>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_map_basic_count()
{
    FILE_BANNER();
    print_section("count() — exist/non-exist");

    ft::map<int, std::string> m;
    m.insert(ft::make_pair(1, "One"));
    m.insert(ft::make_pair(2, "Two"));
    std::cout << "count(1): " << m.count(1) << '\n';
    assert(m.count(1) == 1);
    std::cout << "count(3): " << m.count(3) << '\n';
    assert(m.count(3) == 0);
}
