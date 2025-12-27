// test_vector_comparisons_strict.cpp
#include <cassert>
#include <iostream>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

void test_vector_comparisons_strict()
{
    FILE_BANNER();
    print_section("comparisons — lexicographical & length/element differences");

    ft::vector<int> a;
    ft::vector<int> b;
    assert(a == b);
    assert(!(a != b));

    ft::vector<int> x(3, 1);
    ft::vector<int> y(3, 1);
    assert(x == y);
    assert(!(x < y) && !(x > y));

    ft::vector<int> p;
    p.push_back(1);
    p.push_back(2);
    ft::vector<int> q;
    q.push_back(1);
    q.push_back(2);
    q.push_back(0);
    assert(p < q);
    assert(q > p);

    ft::vector<int> r;
    r.push_back(1);
    r.push_back(3);
    assert(p < r);
    assert(r > p);

    assert(x <= y && x >= y);

    ft::vector<int> s;
    s.push_back(2);
    s.push_back(0);
    ft::vector<int> t;
    t.push_back(2);
    t.push_back(1);
    assert(s < t);

    print_section("comparisons — strict OK");
}
