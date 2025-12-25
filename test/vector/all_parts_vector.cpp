// test_vector_parts.cpp
#include "test_print.h"

#ifndef TEST_VECTOR_PART_1
    #define TEST_VECTOR_PART_1 0
#endif
#ifndef TEST_VECTOR_PART_2
    #define TEST_VECTOR_PART_2 0
#endif

#if TEST_VECTOR_PART_1
void test_vector_constructors();
void test_vector_assignment();
void test_vector_capacity();
void test_vector_element_access();
void test_vector_at_exception();
#endif

#if TEST_VECTOR_PART_2
void test_vector_push_pop();
void test_vector_insert_erase();
void test_vector_clear();
void test_vector_resize_reserve();
void test_vector_iterators();
void test_vector_comparisons();
#endif

void test_vector_part_1()
{
#if TEST_VECTOR_PART_1
    print_section("Vector Part 1 — Constructors / Assignment / Capacity / Access");
    test_vector_constructors();
    test_vector_assignment();
    test_vector_capacity();
    test_vector_element_access();
    test_vector_at_exception();
#else
    (void)0; // no-op
#endif
}

void test_vector_part_2()
{
#if TEST_VECTOR_PART_2
    print_section("Vector Part 2 — Modifiers / Iterators / Comparisons");
    test_vector_push_pop();
    test_vector_insert_erase();
    test_vector_clear();
    test_vector_resize_reserve();
    test_vector_iterators();
    test_vector_comparisons();
#else
    (void)0; // no-op
#endif
}
