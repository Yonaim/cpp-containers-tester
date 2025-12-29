#include <cassert>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_map_basic_insert_plain()
{
    FILE_BANNER();
    print_section("Insert (no balance tests) — duplicate, size/empty invariants");

    ft::map<int, std::string> m;
    print_bool(m.empty());
    assert(m.size() == 0);

    ft::pair<ft::map<int, std::string>::iterator, bool> r;
    r = m.insert(ft::make_pair(10, "Ten"));
    assert(r.second);
    r = m.insert(ft::make_pair(5, "Five"));
    assert(r.second);
    r = m.insert(ft::make_pair(20, "Twenty"));
    assert(r.second);
    r = m.insert(ft::make_pair(10, "Ten-again"));
    print_bool(!r.second);
    std::cout << "key=10 value: " << r.first->second << '\n';
    assert(r.first->second == "Ten");

    print_bool(!m.empty());
    std::cout << "size: " << m.size() << '\n';
    print_tree(m, "After plain inserts");
}
