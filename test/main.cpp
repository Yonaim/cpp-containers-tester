#include <iostream>
#include "test_config.h"
#include "test_print.h"

void test_utils_dispatch();
void test_vector_dispatch();
void test_map_dispatch();
void test_stack_dispatch();

// ============================= Prototypes ============================= //
// NOTE: 파일명이 대표 함수명

// ---------- Utils ----------
#if TEST_UTILS_BASIC
void test_utils_basic_pair();
void test_utils_basic_equal();
void test_utils_basic_lexicographical_compare();
void test_utils_basic_enable_if();
void test_utils_basic_is_integral();
void test_utils_basic_iterator_traits();
void test_utils_basic_reverse_iterator();
#endif

#if TEST_UTILS_STRESS
void test_utils_stress_pair();
void test_utils_stress_compare();
#endif

#if TEST_UTILS_PERF
void test_utils_perf_pair();
void test_utils_perf_compare();
#endif

// ---------- Vector ----------
#if TEST_VECTOR_BASIC
void test_vector_basic_constructors();
void test_vector_basic_assignment();
void test_vector_basic_capacity();
void test_vector_basic_element_access();
void test_vector_basic_at_exception();
void test_vector_basic_push_pop();
void test_vector_basic_insert_erase();
void test_vector_basic_clear();
void test_vector_basic_resize_reserve();
void test_vector_basic_iterators();
void test_vector_basic_comparisons();
void test_vector_basic_element_access_strict();
void test_vector_basic_iterators_strict();
void test_vector_basic_comparisons_strict();
void test_vector_basic_exception_safety();
void test_vector_basic_lifetime_leakcheck();
void test_vector_basic_reallocation_stats();
#endif

#if TEST_VECTOR_STRESS
void test_vector_stress_push_back();
void test_vector_stress_insert();
void test_vector_stress_erase();
void test_vector_stress_buffer_ram();
#endif

#if TEST_VECTOR_PERF
void test_vector_perf_push_back();
void test_vector_perf_random_access();
void test_vector_perf_reallocation();
#endif

// ---------- Map ----------
#if TEST_MAP_BASIC
void test_map_basic_rbt_node();
void test_map_basic_iterators_basic();
void test_map_basic_insert_plain();
void test_map_basic_find_bracket();
void test_map_basic_insert_balance();
void test_map_basic_erase_balance();
void test_map_basic_clear_swap();
void test_map_basic_count();
void test_map_basic_bounds();
void test_map_basic_compare();
void test_map_basic_insert_equal();
void test_map_basic_exception_safety();
void test_map_basic_operator_bracket_insert();
void test_map_basic_copy_assign_self();
void test_map_basic_iterators_strict();
#endif

#if TEST_MAP_STRESS
void test_map_stress_insert();
void test_map_stress_erase();
void test_map_stress_sum_determinism();
#endif

#if TEST_MAP_PERF
void test_map_perf_insert();
void test_map_perf_find();
#endif

// ---------- Stack ----------
#if TEST_STACK_BASIC
void test_stack_basic_constructors_empty_size();
void test_stack_basic_push_top_pop();
void test_stack_basic_types_strings();
void test_stack_basic_comparisons();
void test_stack_basic_underlying_container();
void test_stack_basic_exception_safety();
void test_stack_basic_comparisons_strict();
void test_stack_basic_performance_smoke();
#endif

#if TEST_STACK_STRESS
void test_stack_stress_push_pop();
void test_stack_stress_mutant_iter();
#endif

#if TEST_STACK_PERF
void test_stack_perf_push_pop();
#endif

// ================================ Main ================================ //

int main()
{
    std::cout.setf(std::ios::unitbuf); // for debug

    // ===== Utils =====
#if TEST_UTILS_BASIC || TEST_UTILS_STRESS || TEST_UTILS_PERF
    print_module_banner("Utils Tests");
    test_utils_dispatch();
#endif

    // ===== Vector =====
#if TEST_VECTOR_BASIC || TEST_VECTOR_STRESS || TEST_VECTOR_PERF
    print_module_banner("Vector Tests");
    test_vector_dispatch();
#endif

    // ===== Map =====
#if TEST_MAP_BASIC || TEST_MAP_STRESS || TEST_MAP_PERF
    print_module_banner("Map Tests");
    test_map_dispatch();
#endif

    // ===== Stack =====
#if TEST_STACK_BASIC || TEST_STACK_STRESS || TEST_STACK_PERF
    print_module_banner("Stack Tests");
    test_stack_dispatch();
#endif
    return 0;
}

// ============================= Group runners ============================= //

void test_utils_dispatch()
{
#if TEST_UTILS_BASIC
    print_section("Utils BASIC");
    test_utils_basic_pair();
    test_utils_basic_equal();
    test_utils_basic_lexicographical_compare();
    test_utils_basic_enable_if();
    test_utils_basic_is_integral();
    test_utils_basic_iterator_traits();
    test_utils_basic_reverse_iterator();
#else
    (void)0;
#endif

#if TEST_UTILS_STRESS
    print_section("Utils STRESS");
    test_utils_stress_pair();
    test_utils_stress_compare();
#else
    (void)0;
#endif

#if TEST_UTILS_PERF
    print_section("Utils PERF");
    test_utils_perf_pair();
    test_utils_perf_compare();
#else
    (void)0;
#endif
}

void test_vector_dispatch()
{
#if TEST_VECTOR_BASIC
    print_section("Vector BASIC");
    test_vector_basic_constructors();
    test_vector_basic_assignment();
    test_vector_basic_capacity();
    test_vector_basic_element_access();
    test_vector_basic_at_exception();
    test_vector_basic_push_pop();
    test_vector_basic_insert_erase();
    test_vector_basic_clear();
    test_vector_basic_resize_reserve();
    test_vector_basic_iterators();
    test_vector_basic_comparisons();
    test_vector_basic_element_access_strict();
    test_vector_basic_iterators_strict();
    test_vector_basic_comparisons_strict();
    test_vector_basic_exception_safety();
    test_vector_basic_lifetime_leakcheck();
    test_vector_basic_reallocation_stats();
#else
    (void)0;
#endif

#if TEST_VECTOR_STRESS
    print_section("Vector STRESS");
    test_vector_stress_push_back();
    test_vector_stress_insert();
    test_vector_stress_erase();
    test_vector_stress_buffer_ram();
#else
    (void)0;
#endif

#if TEST_VECTOR_PERF
    print_section("Vector PERF");
    test_vector_perf_push_back();
    test_vector_perf_random_access();
    test_vector_perf_reallocation();
#else
    (void)0;
#endif
}

void test_map_dispatch()
{
#if TEST_MAP_BASIC
    print_section("Map BASIC");
    test_map_basic_rbt_node();
    test_map_basic_iterators_basic();
    test_map_basic_insert_plain();
    test_map_basic_find_bracket();
    test_map_basic_insert_balance();
    test_map_basic_erase_balance();
    test_map_basic_clear_swap();
    test_map_basic_count();
    test_map_basic_bounds();
    test_map_basic_compare();
    test_map_basic_insert_equal();
    test_map_basic_exception_safety();
    test_map_basic_operator_bracket_insert();
    test_map_basic_copy_assign_self();
    test_map_basic_iterators_strict();
#else
    (void)0;
#endif

#if TEST_MAP_STRESS
    print_section("Map STRESS");
    test_map_stress_insert();
    test_map_stress_erase();
    test_map_stress_sum_determinism();
#else
    (void)0;
#endif

#if TEST_MAP_PERF
    print_section("Map PERF");
    test_map_perf_insert();
    test_map_perf_find();
#else
    (void)0;
#endif
}

void test_stack_dispatch()
{
#if TEST_STACK_BASIC
    print_section("Stack BASIC");
    test_stack_basic_constructors_empty_size();
    test_stack_basic_push_top_pop();
    test_stack_basic_types_strings();
    test_stack_basic_comparisons();
    test_stack_basic_underlying_container();
    test_stack_basic_exception_safety();
    test_stack_basic_comparisons_strict();
    test_stack_basic_performance_smoke();
#else
    (void)0;
#endif

#if TEST_STACK_STRESS
    print_section("Stack STRESS");
    test_stack_stress_push_pop();
    test_stack_stress_mutant_iter();
#else
    (void)0;
#endif

#if TEST_STACK_PERF
    print_section("Stack PERF");
    test_stack_perf_push_pop();
#else
    (void)0;
#endif
}

// Optional: one-shot runner in the requested order: Utils -> Vector -> Map -> Stack
void test_all_dispatch()
{
    test_utils_dispatch();
    test_vector_dispatch();
    test_map_dispatch();
    test_stack_dispatch();
}
