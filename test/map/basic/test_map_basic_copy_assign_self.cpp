// test_map_basic_copy_assign_self.cpp
#include <cassert>
#include <iostream>
#include <string>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

static void fill(ft::map<int, std::string> &m)
{
    m.insert(ft::make_pair(3, std::string("c")));
    m.insert(ft::make_pair(1, std::string("a")));
    m.insert(ft::make_pair(2, std::string("b")));
}

static void assert_equal(const ft::map<int, std::string> &a, const ft::map<int, std::string> &b)
{
    assert(a.size() == b.size());
    ft::map<int, std::string>::const_iterator ia = a.begin();
    ft::map<int, std::string>::const_iterator ib = b.begin();
    // for (; ia != a.end() && ib != b.end(); ++ia, ++ib)
    for (; ia != a.end(); ++ia, ++ib)
    {
        std::cout << "elem: " << ia->first << std::endl;
        assert(ia->first == ib->first);
        assert(ia->second == ib->second);
    }
    assert(ia == a.end());
    assert(ib == b.end());
}

void test_map_basic_copy_assign_self()
{
    FILE_BANNER();
    print_section("copy ctor / assignment / self-assign / swap");

    ft::map<int, std::string> m;
    fill(m);

    std::cout << "????" << std::endl;
    // copy constructor
    ft::map<int, std::string> cpy(m);
    assert_equal(m, cpy);

    // assignment
    ft::map<int, std::string> asg;
    asg = m;
    assert_equal(m, asg);

    // self-assignment must be safe
    asg = asg;
    assert_equal(m, asg);

    // swap
    ft::map<int, std::string> other;
    other.insert(ft::make_pair(9, std::string("nine")));
    other.insert(ft::make_pair(8, std::string("eight")));

    size_t msz = m.size();
    size_t osz = other.size();

    m.swap(other);
    assert(m.size() == osz);
    assert(other.size() == msz);

    assert(m.find(9) != m.end() && m.find(9)->second == "nine");
    assert(other.find(1) != other.end() && other.find(1)->second == "a");

    print_section("copy/assign/swap — OK");
}
