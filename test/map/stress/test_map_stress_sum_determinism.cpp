#include "test_print.h"
#include "test_namespace.h"
#include "test_stress_util.h"

// Inspired by the classic Ecole42 map stress:
//  - insert many random (k,v)
//  - repeatedly access random keys via operator[] and sum values
//  - create a copy in a nested scope (copy ctor + dtor)
// The sum should be deterministic for the same seed.
// We fold the sum into the checksum for easy STD vs FT diffing.
//
// Env knobs:
//  STRESS_SEED (u64)           default: 110
//  STRESS_COUNT (size_t)       default: 200000
//  STRESS_ACCESS (size_t)      default: 10000
//  STRESS_KEY_RANGE (size_t)   default: 0 (0 => full int range from RNG)

struct MapSumCtx
{
    ft::map<int, int> *m;
    u64                sum;
    MapSumCtx() : m(0), sum(0) {}

    u64 checksum() const
    {
        u64 h = checksum_range(m->begin(), m->end());
        h = mix_u64(h, sum);
        return h;
    }
    size_t size() const { return (size_t)m->size(); }
};

struct MapSumBody
{
    void operator()(MapSumCtx &ctx, StressRng &rng, size_t /*ops*/) const
    {
        ft::map<int, int> &mp = *ctx.m;

        const size_t count     = env_sz("STRESS_COUNT", 200000);
        const size_t access_n  = env_sz("STRESS_ACCESS", 10000);
        const size_t key_range = env_sz("STRESS_KEY_RANGE", 0);

        mp.clear();

        for (size_t i = 0; i < count; ++i)
        {
            int k = (key_range ? (int)rng.index(key_range) : rng.next_int());
            int v = rng.next_int();
            mp.insert(ft::make_pair(k, v));
        }

        u64 sum = 0;
        for (size_t i = 0; i < access_n; ++i)
        {
            int k = (key_range ? (int)rng.index(key_range) : rng.next_int());
            sum += (u64)mp[k]; // operator[] (default inserts 0 for missing)
        }
        ctx.sum = sum;

        // copy lifetime test
        {
            ft::map<int, int> copy = mp;
            (void)copy;
        }
    }
};

void test_map_stress_sum_determinism()
{
    const u64 seed = env_u64("STRESS_SEED", 110ULL);
    const size_t ops = env_sz("STRESS_OPS", 1); // unused

    ft::map<int, int> mp;
    MapSumCtx ctx;
    ctx.m = &mp;

    StressRunStats st = run_stress_case("map_stress_sum_determinism", ctx, MapSumBody(), seed, ops);

    // Extra human-friendly line (optional)
    std::cout << "  should_be_constant_sum=" << (unsigned long long)ctx.sum << "\n";
    (void)st;
}
