// test_vector_basic_lifetime_leakcheck.cpp
#include <cassert>
#include <iostream>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

struct Counted
{
    static int alive;
    int        x;
    Counted() : x(0) { ++alive; }
    Counted(int v) : x(v) { ++alive; }
    Counted(const Counted &c) : x(c.x) { ++alive; }
    Counted &operator=(const Counted &c)
    {
        x = c.x;
        return *this;
    }
    ~Counted() { --alive; }
};
int Counted::alive = 0;

static void dump(const ft::vector<Counted> &v, const char *tag)
{
    std::cout << tag << " [size=" << v.size() << ", alive=" << Counted::alive << "]: ";
    for (size_t i = 0; i < v.size(); ++i)
        std::cout << v[i].x << ' ';
    std::cout << '\n';
}

void test_vector_basic_lifetime_leakcheck()
{
    FILE_BANNER();
    print_section("lifetime/leak — clear/erase/resize destroy semantics");

    assert(Counted::alive == 0);
    {
        ft::vector<Counted> v;
        for (int i = 0; i < 8; ++i)
            v.push_back(Counted(i));
        assert(Counted::alive == 8);
        dump(v, "init");

        v.erase(v.begin() + 3);
        assert(Counted::alive == 7);
        v.erase(v.begin(), v.begin() + 2);
        assert(Counted::alive == 5);
        dump(v, "after erases");

        v.resize(10, Counted(42));
        assert(Counted::alive == 10);
        dump(v, "after resize up");

        v.resize(4);
        assert(Counted::alive == 4);
        dump(v, "after resize down");

        v.clear();
        assert(Counted::alive == 0);
        dump(v, "after clear");
    }
    assert(Counted::alive == 0);
    print_section("lifetime/leak — all destroyed, no leaks");
}
