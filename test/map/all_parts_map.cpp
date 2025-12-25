#include "test_print.h"

#ifndef TEST_MAP_PART_1
#  define TEST_MAP_PART_1 0
#endif
#ifndef TEST_MAP_PART_2
#  define TEST_MAP_PART_2 0
#endif
#ifndef TEST_MAP_PART_3
#  define TEST_MAP_PART_3 0
#endif

#if TEST_MAP_PART_1
void test_map_rbt_node();
void test_map_iterators_basic();
void test_map_insert_plain();
void test_map_find_bracket();
#endif

#if TEST_MAP_PART_2
void test_map_insert_balance();
void test_map_erase_balance();
void test_map_clear_swap();
void test_map_count();
#endif

#if TEST_MAP_PART_3
void test_map_bounds();
void test_map_compare();
#endif

void test_map_part_1()
{
#if TEST_MAP_PART_1
    print_section("Map Part 1 — Node/Iterators/Plain Insert/Find & []");
    test_map_rbt_node();
    test_map_iterators_basic();
    test_map_insert_plain();
    test_map_find_bracket();
#else
    (void)0;
#endif
}

void test_map_part_2()
{
#if TEST_MAP_PART_2
    print_section("Map Part 2 — Insert Balance / Erase Balance / clear/swap / count");
    test_map_insert_balance();
    test_map_erase_balance();
    test_map_clear_swap();
    test_map_count();
#else
    (void)0;
#endif
}

void test_map_part_3()
{
#if TEST_MAP_PART_3
    print_section("Map Part 3 — bounds / compare");
    test_map_bounds();
    test_map_compare();
#else
    (void)0;
#endif
}
