#include "test_print.h"

#ifndef TEST_STACK
#  define TEST_STACK 0
#endif
#ifndef TEST_STACK_ADV
#  define TEST_STACK_ADV 0
#endif

#if TEST_STACK
void test_stack_constructors_empty_size();
void test_stack_push_top_pop();
void test_stack_types_strings();
void test_stack_comparisons();
#endif

#if TEST_STACK_ADV
void test_stack_underlying_container();
void test_stack_exception_safety();
void test_stack_comparisons_strict();
void test_stack_performance_smoke();
#endif

void test_stack()
{
#if TEST_STACK
    print_section("Stack Core — ctor/empty/size, push/top/pop, types, comparisons");
    test_stack_constructors_empty_size();
    test_stack_push_top_pop();
    test_stack_types_strings();
    test_stack_comparisons();
#else
    (void)0;
#endif

#if TEST_STACK_ADV
    print_section("Stack Advanced — underlying container / exception / strict / perf");
    test_stack_underlying_container();
    test_stack_exception_safety();
    test_stack_comparisons_strict();
    test_stack_performance_smoke();
#endif
}
