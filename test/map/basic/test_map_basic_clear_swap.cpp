#include <cassert>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_map_basic_clear_swap()
{
    FILE_BANNER();
    print_section("clear() / swap()");

    ft::map<int, std::string> a, b;
    for (int i = 0; i < 5; ++i)
        a.insert(ft::make_pair(i, "A"));
    for (int i = 5; i < 8; ++i)
        b.insert(ft::make_pair(i, "B"));

    std::cout << "Before swap:\n";
    print_tree(a, "a");
    print_tree(b, "b");
    a.swap(b);
    std::cout << "After swap:\n";
    print_tree(a, "a(after)");
    print_tree(b, "b(after)");

    a.clear();
    std::cout << "After a.clear(): size=" << a.size()
              << ", empty=" << (a.empty() ? "true" : "false") << '\n';
    assert(a.size() == 0 && a.empty());
}
