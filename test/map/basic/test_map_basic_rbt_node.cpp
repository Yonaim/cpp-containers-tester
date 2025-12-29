#include <cassert>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_map_basic_rbt_node()
{
    FILE_BANNER();
    print_section("RBT Node — basic structure smoke (insert + in-order shape)");

    ft::map<int, std::string> m;
    int                       ks[] = {10, 5, 15, 3, 7, 12, 18};
    const char               *vs[] = {"10", "5", "15", "3", "7", "12", "18"};
    for (int i = 0; i < 7; ++i)
    {
        ft::pair<ft::map<int, std::string>::iterator, bool> r =
            m.insert(ft::make_pair(ks[i], vs[i]));
        assert(r.second);
    }
    assert(m.size() == 7);
    print_tree(m, "After inserts (expect inorder: 3 5 7 10 12 15 18)");
}
