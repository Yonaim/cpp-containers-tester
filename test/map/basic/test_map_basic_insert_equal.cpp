// test_map_basic_insert_equal.cpp
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

// 중복 키 insert가 "무시"되는지(값 덮어쓰지 않음) + 3가지 insert 오버로드 확인
// - insert(value) -> pair<it,bool>
// - insert(hint, value) -> it
// - insert(range) -> 중복 무시 + 새 키만 추가

static void assert_map_kv(const ft::map<int, std::string> &m,
                          const int *keys, const char **vals, size_t n)
{
    assert(m.size() == n);
    size_t i = 0;
    for (ft::map<int, std::string>::const_iterator it = m.begin(); it != m.end(); ++it, ++i)
    {
        assert(i < n);
        assert(it->first == keys[i]);
        assert(it->second == std::string(vals[i]));
    }
    assert(i == n);
}

void test_map_basic_insert_equal()
{
    FILE_BANNER();
    print_section("insert_equal — duplicates are ignored (no overwrite)");

    ft::map<int, std::string> m;
    m.insert(ft::make_pair(2, std::string("two")));
    m.insert(ft::make_pair(1, std::string("one")));
    m.insert(ft::make_pair(3, std::string("three")));

    // ---- 1) insert(value): duplicate key
    {
        ft::pair< ft::map<int, std::string>::iterator, bool > r =
            m.insert(ft::make_pair(2, std::string("TWO_NEW")));
        assert(r.second == false);                 // 삽입 실패
        assert(r.first->first == 2);
        assert(r.first->second == "two");          // 기존 값 유지(덮어쓰기 X)
        assert(m.size() == 3);
    }
    print_section("insert(value): duplicate ignored, value preserved");

    // ---- 2) insert(hint, value): duplicate key
    {
        ft::map<int, std::string>::iterator hint = m.begin(); // 아무 힌트
        ft::map<int, std::string>::iterator it =
            m.insert(hint, ft::make_pair(1, std::string("ONE_NEW")));
        assert(it->first == 1);
        assert(it->second == "one");               // 기존 값 유지
        assert(m.size() == 3);
    }
    print_section("insert(hint,value): duplicate ignored, value preserved");

    // ---- 3) insert(range): duplicates + new keys mixed
    {
        std::vector< ft::pair<int, std::string> > v;
        v.push_back(ft::make_pair(0, std::string("zero")));   // new
        v.push_back(ft::make_pair(2, std::string("TWO_X")));  // dup
        v.push_back(ft::make_pair(4, std::string("four")));   // new
        v.push_back(ft::make_pair(1, std::string("ONE_X")));  // dup

        m.insert(v.begin(), v.end());

        const int   keys[] = {0, 1, 2, 3, 4};
        const char *vals[] = {"zero", "one", "two", "three", "four"};
        assert_map_kv(m, keys, vals, 5);
    }
    print_section("insert(range): only new keys inserted, dups ignored");

    // ---- insert return iterator points to existing element for duplicate
    {
        ft::pair< ft::map<int, std::string>::iterator, bool > r =
            m.insert(ft::make_pair(3, std::string("THREE_X")));
        assert(r.second == false);
        assert(r.first != m.end());
        assert(r.first->first == 3);
        assert(r.first->second == "three");
    }
    print_section("insert return iterator points to existing element");
}
