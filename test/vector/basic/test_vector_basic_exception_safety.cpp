// test_vector_basic_exception_safety.cpp
#include <cassert>
#include <iostream>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

struct Bomb
{
    static int copy_count;
    static int throw_after;
    int        value;
    Bomb() : value(0) {}
    Bomb(int v) : value(v) {}
    Bomb(const Bomb &other) : value(other.value)
    {
        ++copy_count;
        if (throw_after >= 0 && copy_count > throw_after)
        {
            throw 1;
        }
    }
    Bomb &operator=(const Bomb &other)
    {
        value = other.value;
        return *this;
    }
};

int Bomb::copy_count = 0;
int Bomb::throw_after = -1;

static void print_vec(const ft::vector<Bomb> &v, const char *tag)
{
    std::cout << tag << " [size=" << v.size() << "]: ";
    for (size_t i = 0; i < v.size(); ++i)
        std::cout << v[i].value << ' ';
    std::cout << '\n';
}

void test_vector_basic_exception_safety()
{
    FILE_BANNER();
    print_section("exception safety — strong guarantee on insert/resize");

    ft::vector<Bomb> v;
    for (int i = 0; i < 6; ++i)
        v.push_back(Bomb(i));
    print_vec(v, "init");

    Bomb::copy_count = 0;
    Bomb::throw_after = 2;

    ft::vector<Bomb> snapshot(v);
    bool             threw = false;
    try
    {
        v.insert(v.begin() + 2, Bomb(999));
    }
    catch (...)
    {
        threw = true;
    }
    assert(threw);
    assert(v.size() == snapshot.size());
    for (size_t i = 0; i < v.size(); ++i)
        assert(v[i].value == snapshot[i].value);
    print_section("insert exception — strong guarantee holds");

    Bomb::copy_count = 0;
    Bomb::throw_after = 1;
    snapshot = v;
    threw = false;
    try
    {
        v.resize(12, Bomb(7));
    }
    catch (...)
    {
        threw = true;
    }
    assert(threw);
    assert(v.size() == snapshot.size());
    for (size_t i = 0; i < v.size(); ++i)
        assert(v[i].value == snapshot[i].value);
    print_section("resize growth exception — strong guarantee holds");

    Bomb::throw_after = -1;
    v.resize(3);
    assert(v.size() == 3);
    for (size_t i = 0; i < 3; ++i)
        assert(v[i].value == (int)i);
    print_section("resize shrink — OK");
}
