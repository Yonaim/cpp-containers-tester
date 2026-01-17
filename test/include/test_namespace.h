#ifndef TEST_NAMESPACE_H
#define TEST_NAMESPACE_H

// ============================================================================
//  Common header to automatically switch between STD and FT implementations
// ============================================================================

#ifdef STD_MODE
    // -----------------------------
    // Use standard library headers
    // -----------------------------
    #include <algorithm>
    #include <functional>
    #include <iterator>
    #include <map>
    #include <memory>
    #include <stack>
    #include <type_traits> // C++11
    #include <utility>
    #include <vector>

namespace ft = std;

#else
    // -----------------------------
    // Use custom ft headers
    // -----------------------------

    #include "algorithm.h"
    #include "ft_memory.h"
    #include "container/map.h"
    #include "container/stack.h"
    #include "container/vector.h"
    #include "container/bvector.h"
    #include "functional.h"
    #include "iterator.h"
    #include "type_traits.h"
    #include "utility.h"

#endif // STD_MODE

#endif // TEST_NAMESPACE_H
