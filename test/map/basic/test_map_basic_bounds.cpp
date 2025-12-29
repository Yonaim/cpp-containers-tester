#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_map_basic_bounds()
{
    FILE_BANNER();
    print_section("lower_bound / upper_bound / equal_range");

    ft::map<int, std::string> m;
    int                       ks[] = {10, 20, 30, 40, 50};
    const char               *vs[] = {"Ten", "Twenty", "Thirty", "Forty", "Fifty"};
    for (int i = 0; i < 5; ++i)
        m.insert(ft::make_pair(ks[i], vs[i]));

    typedef ft::map<int, std::string>::iterator it_t;
    it_t                                        low = m.lower_bound(25);
    it_t                                        up = m.upper_bound(30);
    print_it("lower_bound(25)", low, m.end());
    print_it("upper_bound(30)", up, m.end());

    ft::pair<it_t, it_t> range = m.equal_range(30);
    print_it("equal_range.first (30)", range.first, m.end());
    print_it("equal_range.second (30)", range.second, m.end());
}
