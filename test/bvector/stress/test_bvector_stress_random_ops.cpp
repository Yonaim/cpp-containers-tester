// test_bvector_stress_random_ops.cpp
// Deterministic random stress for vector<bool> behavior.
#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

#include "test_config.h"
#include "test_namespace.h"
#include "test_print.h"

struct Lcg
{
    unsigned int state;
    Lcg(unsigned int seed) : state(seed) {}
    unsigned int next_u32()
    {
        // Numerical Recipes LCG
        state = state * 1664525u + 1013904223u;
        return state;
    }
    size_t next_idx(size_t mod)
    {
        if (mod == 0)
            return 0;
        return static_cast<size_t>(next_u32() % mod);
    }
    bool next_bit() { return (next_u32() & 1u) != 0; }
};

static void full_check(const ft::vector<bool> &v, const std::vector<unsigned char> &ref)
{
    assert(v.size() == ref.size());
    for (size_t i = 0; i < ref.size(); ++i)
        assert((bool)v[i] == (ref[i] != 0));
}

void test_bvector_stress_random_ops()
{
    FILE_BANNER();
    print_section("bvector stress — random ops (oracle: std::vector<unsigned char>)");

    ft::vector<bool> v;
    std::vector<unsigned char> ref;
    Lcg rng(0xC0FFEEu);

    const size_t STEPS = 5000;
    const size_t MAX_N = 512;

    for (size_t step = 0; step < STEPS; ++step)
    {
        unsigned int op = rng.next_u32() % 9u;

        if (op == 0)
        {
            // push_back
            bool b = rng.next_bit();
            v.push_back(b);
            ref.push_back((unsigned char)(b ? 1 : 0));
        }
        else if (op == 1)
        {
            // pop_back
            if (!ref.empty())
            {
                v.pop_back();
                ref.pop_back();
            }
        }
        else if (op == 2)
        {
            // insert single
            if (ref.size() < MAX_N)
            {
                size_t pos = rng.next_idx(ref.size() + 1);
                bool b = rng.next_bit();
                v.insert(v.begin() + (typename ft::vector<bool>::difference_type)pos, b);
                ref.insert(ref.begin() + (std::ptrdiff_t)pos, (unsigned char)(b ? 1 : 0));
            }
        }
        else if (op == 3)
        {
            // erase single
            if (!ref.empty())
            {
                size_t pos = rng.next_idx(ref.size());
                v.erase(v.begin() + (typename ft::vector<bool>::difference_type)pos);
                ref.erase(ref.begin() + (std::ptrdiff_t)pos);
            }
        }
        else if (op == 4)
        {
            // flip one bit via proxy assignment
            if (!ref.empty())
            {
                size_t pos = rng.next_idx(ref.size());
                bool cur = (ref[pos] != 0);
                v[pos] = !cur;
                ref[pos] = (unsigned char)(cur ? 0 : 1);
            }
        }
        else if (op == 5)
        {
            // range insert small
            if (ref.size() < MAX_N)
            {
                size_t pos = rng.next_idx(ref.size() + 1);
                size_t k = (size_t)(rng.next_u32() % 8u);
                if (ref.size() + k > MAX_N)
                    k = MAX_N - ref.size();
                bool b = rng.next_bit();
                v.insert(v.begin() + (typename ft::vector<bool>::difference_type)pos, k, b);
                ref.insert(ref.begin() + (std::ptrdiff_t)pos, k, (unsigned char)(b ? 1 : 0));
            }
        }
        else if (op == 6)
        {
            // resize
            size_t new_sz = (size_t)(rng.next_u32() % (MAX_N + 1));
            bool fill = rng.next_bit();
            v.resize(new_sz, fill);
            ref.resize(new_sz, (unsigned char)(fill ? 1 : 0));
        }
        else if (op == 7)
        {
            // clear
            v.clear();
            ref.clear();
        }
        else
        {
            // reserve (monotonic)
            size_t want = (size_t)(rng.next_u32() % (MAX_N + 1));
            v.reserve(want);
            assert(v.capacity() >= want);
        }

        // cheap checks
        assert(v.size() == ref.size());
        if (!ref.empty())
        {
            size_t i = rng.next_idx(ref.size());
            assert((bool)v[i] == (ref[i] != 0));
        }

        if ((step % 200) == 0)
            full_check(v, ref);
    }

    full_check(v, ref);
    std::cout << "Final size=" << v.size() << ", cap=" << v.capacity() << "\n";
}
