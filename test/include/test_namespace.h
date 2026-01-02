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

    // TODO : include your implemented headers

#endif // STD_MODE

#endif // TEST_NAMESPACE_H
