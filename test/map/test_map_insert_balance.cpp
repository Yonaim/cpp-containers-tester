#include <cassert>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_map_insert_balance()
{
    FILE_BANNER();
    print_section("Insert balancing — sample rotations/recolors");

    ft::map<int, std::string> m;
    int                       seq[] = {30, 15, 40, 10, 20, 35, 50, 5, 12, 18, 25};
    for (size_t i = 0; i < sizeof(seq) / sizeof(seq[0]); ++i)
        m.insert(ft::make_pair(seq[i], ""));

    assert(m.size() == sizeof(seq) / sizeof(seq[0]));
    print_tree(m, "After inserts (inspect RB properties visually)");
}
