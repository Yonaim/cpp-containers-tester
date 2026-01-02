// test_map_basic_operator_bracket_insert.cpp
#include <cassert>
#include <iostream>
#include <string>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_map_basic_operator_bracket_insert()
{
    FILE_BANNER();
    print_section("operator[] — inserts default on missing key, returns reference");

    ft::map<int, std::string> m;

    // missing key -> default insert("") then reference returned
    assert(m.size() == 0);
    m[10] = "ten";
    assert(m.size() == 1);
    assert(m.find(10) != m.end());
    assert(m.find(10)->second == "ten");

    // existing key -> does NOT insert, just returns reference
    size_t before = m.size();
    m[10] = "TEN";
    assert(m.size() == before);
    assert(m.find(10)->second == "TEN");

    // missing key but read-access triggers default insert
    before = m.size();
    std::string &ref = m[20];
    assert(m.size() == before + 1);
    assert(ref == "");            // default constructed
    ref = "twenty";
    assert(m.find(20)->second == "twenty");

    print_section("operator[] semantics — OK");
}
