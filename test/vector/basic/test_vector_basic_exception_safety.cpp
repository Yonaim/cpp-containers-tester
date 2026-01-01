/*
    insert / resize 도중 예외가 발생하면
    vector는 이전 상태를 그대로 유지해야 한다 (strong guarantee)
*/

#include <cassert>
#include <iostream>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

struct Bomb
{
    static bool explode;
    int         value;

    Bomb(int v = 0) : value(v) {}

    Bomb(const Bomb &other) : value(other.value)
    {
        if (explode)
            throw 1;
    }

    Bomb &operator=(const Bomb &other)
    {
        value = other.value;
        return *this;
    }
};

bool Bomb::explode = false;

void test_vector_basic_exception_safety()
{
    FILE_BANNER();
    print_section("exception safety — strong guarantee");

    ft::vector<Bomb> v;
    for (int i = 0; i < 6; ++i)
        v.push_back(Bomb(i));

    ft::vector<Bomb> snapshot(v);

    // ---------------- insert ----------------
    Bomb::explode = true;
    bool threw = false;
    try
    {
        v.insert(v.begin() + 2, Bomb(999));
    }
    catch (...)
    {
        threw = true;
    }
    Bomb::explode = false;

    assert(threw);
    assert(v.size() == snapshot.size());
    for (size_t i = 0; i < v.size(); ++i)
        assert(v[i].value == snapshot[i].value);

    print_section("insert exception — strong guarantee holds");

    // ---------------- resize (grow) ----------------
    snapshot = v;
    Bomb::explode = true;
    threw = false;
    try
    {
        v.resize(12, Bomb(7));
    }
    catch (...)
    {
        threw = true;
    }
    Bomb::explode = false;

    assert(threw);
    assert(v.size() == snapshot.size());
    for (size_t i = 0; i < v.size(); ++i)
        assert(v[i].value == snapshot[i].value);

    print_section("resize growth exception — strong guarantee holds");

    // ---------------- resize (shrink) ----------------
    v.resize(3);
    assert(v.size() == 3);
    for (size_t i = 0; i < 3; ++i)
        assert(v[i].value == (int)i);

    print_section("resize shrink — OK");
}
