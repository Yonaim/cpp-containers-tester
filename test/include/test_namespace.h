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

    // ========== algorithm ==========
    #include "algorithm/equal.h"
    #include "algorithm/lexicographical_compare.h"

    // ========== allocator ==========
    #include "allocator/allocator.h"

    // ========== container ==========
    #include "container/map.h"
    #include "container/stack.h"
    #include "container/vector.h"

    // ========== functional ==========
    #include "functional/binary_function.h"
    #include "functional/equal_to.h"
    #include "functional/less.h"
    #include "functional/select1st.h"
    #include "functional/unary_function.h"

    // ========== iterator ==========
    #include "iterator/distance.h"
    #include "iterator/iterator_tags.h"
    #include "iterator/iterator_traits.h"
    #include "iterator/reverse_iterator.h"

    // ========== tree (RB-tree internals) ==========
    #include "tree/rb_tree.h"
    #include "tree/rb_tree_impl.h"
    #include "tree/rb_tree_iterator.h"
    #include "tree/rb_tree_node.h"

    // ========== type_traits ==========
    #include "type_traits/bool_type.h"
    #include "type_traits/enable_if.h"
    #include "type_traits/is_floating_point.h"
    #include "type_traits/is_integral.h"
    #include "type_traits/remove_cv.h"

    // ========== utility ==========
    #include "utility/pair.h"

#endif // STD_MODE

#endif // TEST_NAMESPACE_H
