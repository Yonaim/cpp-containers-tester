#include <cassert>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_map_erase_balance()
{
    FILE_BANNER();
    print_section("Erase + delete-balancing — leaf/one-child/two-children");

    ft::map<int, std::string> m;
    int                       ks[] = {20, 10, 30, 5, 15, 25, 40, 2, 7, 13, 17};
    for (int i = 0; i < 11; ++i)
        m.insert(ft::make_pair(ks[i], "v"));

    print_tree(m, "Initial");

    size_t removed = m.erase(2);
    std::cout << "erase(2) -> " << removed << '\n';
    assert(removed == 1);

    removed = m.erase(5);
    std::cout << "erase(5) -> " << removed << '\n';
    assert(removed == 1);

    removed = m.erase(10);
    std::cout << "erase(10) -> " << removed << '\n';
    assert(removed == 1);

    print_tree(m, "After erases (inspect RB properties visually)");
}
