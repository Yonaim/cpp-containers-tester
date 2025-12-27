#include <iostream>
#include "test_config.h"
#include "test_core.h"
#include "test_print.h"

// ===== 기본값: 전부 OFF =====
// Utils: Part 1~2
#ifndef TEST_UTILS_PART_1
    #define TEST_UTILS_PART_1 0
#endif
#ifndef TEST_UTILS_PART_2
    #define TEST_UTILS_PART_2 0
#endif

// Vector: Part 1~2
#ifndef TEST_VECTOR_PART_1
    #define TEST_VECTOR_PART_1 0
#endif
#ifndef TEST_VECTOR_PART_2
    #define TEST_VECTOR_PART_2 0
#endif

// Map: Part 1~3
#ifndef TEST_MAP_PART_1
    #define TEST_MAP_PART_1 0
#endif
#ifndef TEST_MAP_PART_2
    #define TEST_MAP_PART_2 0
#endif
#ifndef TEST_MAP_PART_3
    #define TEST_MAP_PART_3 0
#endif

// Stack: 단일
#ifndef TEST_STACK
    #define TEST_STACK 0
#endif

int main()
{
    std::cout.setf(std::ios::unitbuf);
    // ===== Utils =====
#if TEST_UTILS_PART_1 || TEST_UTILS_PART_2
    print_module_banner("Utils Tests");
    #if TEST_UTILS_PART_1
    // Utils Part 1
    test_utils_pair();
    test_utils_equal();
    test_utils_lexicographical_compare();
    #endif
    #if TEST_UTILS_PART_2
    // Utils Part 2
    test_utils_enable_if();
    test_utils_is_integral();
    test_utils_iterator_traits();
    test_utils_reverse_iterator();
    #endif
#endif

    // ===== Vector =====
#if TEST_VECTOR_PART_1 || TEST_VECTOR_PART_2
    print_module_banner("Vector Tests");
    #if TEST_VECTOR_PART_1
    test_vector_part_1();
    #endif
    #if TEST_VECTOR_PART_2
    test_vector_part_2();
    #endif
#endif

    // ===== Map =====
#if TEST_MAP_PART_1 || TEST_MAP_PART_2 || TEST_MAP_PART_3
    print_module_banner("Map Tests");
    #if TEST_MAP_PART_1
    test_map_part_1();
    #endif
    #if TEST_MAP_PART_2
    test_map_part_2();
    #endif
    #if TEST_MAP_PART_3
    test_map_part_3();
    #endif
#endif

    // ===== Stack =====
#if TEST_STACK
    print_module_banner("Stack Tests");
    test_stack();
#endif

    return 0;
}
