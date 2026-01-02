// test_map_basic_exception_safety.cpp
/*
    map::insert / operator[] 도중 예외가 발생하면
    map은 이전 상태를 그대로 유지해야 한다 (strong guarantee)
*/

#include <cassert>
#include <iostream>
#include <vector>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

struct Bomb
{
    static bool explode_copy;
    int         value;

    Bomb(int v = 0) : value(v) {}

    Bomb(const Bomb &other) : value(other.value)
    {
        if (explode_copy)
            throw 1;
    }

    Bomb &operator=(const Bomb &other)
    {
        value = other.value;
        return *this;
    }
};

bool Bomb::explode_copy = false;

// operator[] 삽입 시 default-construct가 터질 수 있음
struct BombDefault
{
    static bool explode_default;
    int         value;

    BombDefault() : value(0)
    {
        if (explode_default)
            throw 2;
    }
    BombDefault(int v) : value(v) {}
    BombDefault(const BombDefault &o) : value(o.value) {}
    BombDefault &operator=(const BombDefault &o) { value = o.value; return *this; }
};

bool BombDefault::explode_default = false;

template <class MapT>
static void snapshot_kv_int_bomb(const MapT &m, std::vector<int> &keys, std::vector<int> &vals)
{
    keys.clear();
    vals.clear();
    for (typename MapT::const_iterator it = m.begin(); it != m.end(); ++it)
    {
        keys.push_back(it->first);
        vals.push_back(it->second.value);
    }
}

template <class MapT>
static void assert_same_kv_int_bomb(const MapT &m,
                                   const std::vector<int> &keys, const std::vector<int> &vals)
{
    assert(m.size() == keys.size());
    typename MapT::const_iterator it = m.begin();
    for (size_t i = 0; i < keys.size(); ++i, ++it)
    {
        assert(it != m.end());
        assert(it->first == keys[i]);
        assert(it->second.value == vals[i]);
    }
    assert(it == m.end());
}

void test_map_basic_exception_safety()
{
    FILE_BANNER();
    print_section("exception safety — strong guarantee (insert / operator[])");

    // ---------------- insert strong guarantee ----------------
    ft::map<int, Bomb> m;
    for (int i = 0; i < 6; ++i)
        m.insert(ft::make_pair(i, Bomb(i * 10)));

    std::vector<int> keys, vals;
    snapshot_kv_int_bomb(m, keys, vals);

    // value_type를 미리 만들어 두고(폭발 OFF), insert 내부 copy에서 터지게 만들기
    ft::pair<const int, Bomb> p(42, Bomb(420));
    Bomb::explode_copy = true;

    bool threw = false;
    try
    {
        m.insert(p); // 여기서 Bomb copy가 터지면 map은 unchanged여야 함
    }
    catch (...)
    {
        threw = true;
    }
    Bomb::explode_copy = false;

    assert(threw);
    assert_same_kv_int_bomb(m, keys, vals);
    print_section("insert exception — strong guarantee holds");

    // ---------------- insert duplicate + exception(중복이면 애초에 생성/할당 최소화되는 구현도 있음)
    // 구현마다 최적화가 달라질 수 있으니, 여기서는 "결과적으로 map이 변하지 않는다"만 보장 검사
    snapshot_kv_int_bomb(m, keys, vals);
    ft::pair<const int, Bomb> dup(3, Bomb(999)); // key=3 already exists
    Bomb::explode_copy = true;
    threw = false;
    try
    {
        m.insert(dup);
    }
    catch (...)
    {
        // 어떤 구현은 중복 판단 전에 value copy를 안 해서 예외가 안 날 수도 있음
        threw = true;
    }
    Bomb::explode_copy = false;

    // 예외가 나든 안 나든, 중복 insert는 결과적으로 map 내용이 동일해야 함
    assert_same_kv_int_bomb(m, keys, vals);
    print_section("duplicate insert (with possible throw) — map unchanged");

    // ---------------- operator[] strong guarantee ----------------
    ft::map<int, BombDefault> md;
    md.insert(ft::make_pair(1, BombDefault(10)));
    md.insert(ft::make_pair(2, BombDefault(20)));

    size_t before_size = md.size();

    BombDefault::explode_default = true;
    threw = false;
    try
    {
        // key=999는 없으므로 operator[]는 삽입 + default construct 시도
        // default ctor가 터지면 map unchanged여야 함
        md[999].value = 777; // 여기까지 못 옴
    }
    catch (...)
    {
        threw = true;
    }
    BombDefault::explode_default = false;

    assert(threw);
    assert(md.size() == before_size);
    assert(md.find(999) == md.end()); // 삽입이 롤백되어야 함
    assert(md.find(1) != md.end() && md.find(1)->second.value == 10);
    assert(md.find(2) != md.end() && md.find(2)->second.value == 20);

    print_section("operator[] insertion exception — strong guarantee holds");
}
