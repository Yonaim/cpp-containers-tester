#ifndef TEST_CONFIG_H
#define TEST_CONFIG_H

#ifdef STD_MODE
namespace std
{
}
namespace ft = std;
#endif

// ===== 기본값: 전부 OFF =====
// Utils
#ifndef TEST_UTILS_BASIC
    #define TEST_UTILS_BASIC 0
#endif
#ifndef TEST_UTILS_STRESS
    #define TEST_UTILS_STRESS 0
#endif
#ifndef TEST_UTILS_PERF
    #define TEST_UTILS_PERF 0
#endif

// Vector
#ifndef TEST_VECTOR_BASIC
    #define TEST_VECTOR_BASIC 0
#endif
#ifndef TEST_VECTOR_STRESS
    #define TEST_VECTOR_STRESS 0
#endif
#ifndef TEST_VECTOR_PERF
    #define TEST_VECTOR_PERF 0
#endif

// Map
#ifndef TEST_MAP_BASIC
    #define TEST_MAP_BASIC 0
#endif
#ifndef TEST_MAP_STRESS
    #define TEST_MAP_STRESS 0
#endif
#ifndef TEST_MAP_PERF
    #define TEST_MAP_PERF 0
#endif

// Stack
#ifndef TEST_STACK_BASIC
    #define TEST_STACK_BASIC 0
#endif
#ifndef TEST_STACK_STRESS
    #define TEST_STACK_STRESS 0
#endif
#ifndef TEST_STACK_PERF
    #define TEST_STACK_PERF 0
#endif

#endif // TEST_CONFIG_H
