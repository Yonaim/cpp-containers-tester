// test_map_basic_iterators_strict.cpp
#include <cassert>
#include <iostream>
#include <string>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_map_basic_iterators_strict()
{
    FILE_BANNER();
    print_section("iterators — const / reverse / ordering strictness");

    ft::map<int, std::string> m;
    m.insert(ft::make_pair(2, std::string("b")));
    m.insert(ft::make_pair(1, std::string("a")));
    m.insert(ft::make_pair(3, std::string("c")));

    // forward order must be sorted by key
    {
        ft::map<int, std::string>::iterator it = m.begin();
        assert(it->first == 1); ++it;
        assert(it->first == 2); ++it;
        assert(it->first == 3); ++it;
        assert(it == m.end());
    }

    // const_iterator traversal
    {
        const ft::map<int, std::string> &cm = m;
        ft::map<int, std::string>::const_iterator it = cm.begin();
        assert(it->first == 1); ++it;
        assert(it->first == 2); ++it;
        assert(it->first == 3); ++it;
        assert(it == cm.end());
    }

    // reverse_iterator traversal
    {
        ft::map<int, std::string>::reverse_iterator rit = m.rbegin();
        assert(rit->first == 3); ++rit;
        assert(rit->first == 2); ++rit;
        assert(rit->first == 1); ++rit;
        assert(rit == m.rend());
    }

    // iterator validity sanity: insert should not invalidate existing iterators in map
    {
        ft::map<int, std::string>::iterator it2 = m.find(2);
        assert(it2 != m.end());
        m.insert(ft::make_pair(4, std::string("d")));
        assert(it2->first == 2);
        assert(it2->second == "b");
    }

    print_section("iterator strictness — OK");
}
