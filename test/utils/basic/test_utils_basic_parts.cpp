// test_utils_basic_parts.cpp
#include "test_print.h"

#ifndef test_utils_basic_PART_1
    #define test_utils_basic_PART_1 0
#endif
#ifndef test_utils_basic_PART_2
    #define test_utils_basic_PART_2 0
#endif

#if test_utils_basic_PART_1
void test_utils_basic_pair();
void test_utils_basic_equal();
void test_utils_basic_lexicographical_compare();
#endif

#if test_utils_basic_PART_2
void test_utils_basic_enable_if();
void test_utils_basic_is_integral();
void test_utils_basic_iterator_traits();
void test_utils_basic_reverse_iterator();
#endif

void test_utils_basic_part_1()
{
#if test_utils_basic_PART_1
    print_section("Utils Part 1 — pair / equal / lexicographical_compare");
    test_utils_basic_pair();
    test_utils_basic_equal();
    test_utils_basic_lexicographical_compare();
#else
    (void)0; // no-op
#endif
}

void test_utils_basic_part_2()
{
#if test_utils_basic_PART_2
    print_section("Utils Part 2 — enable_if / is_integral / iterator_traits / reverse_iterator");
    test_utils_basic_enable_if();
    test_utils_basic_is_integral();
    test_utils_basic_iterator_traits();
    test_utils_basic_reverse_iterator();
#else
    (void)0; // no-op
#endif
}
