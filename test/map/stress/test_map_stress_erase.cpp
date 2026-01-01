#include "test_print.h"
#include "test_namespace.h"
#include "test_stress_util.h"

// Env knobs:
//  STRESS_SEED (u64)           default: 11
//  STRESS_OPS (size_t)         default: 200000
//  STRESS_KEY_RANGE (size_t)   default: 200000
//
// Focus: erase(key), with some inserts to keep the tree populated.

struct MapEraseBody
{
    template <class Map>
    void operator()(MapCtx<Map> &ctx, StressRng &rng, size_t ops) const
    {
        Map &m = *ctx.m;
        const size_t kr = (ctx.key_range ? ctx.key_range : 1);

        // Warm-up: fill some keys
        const size_t warm = (kr < 10000 ? kr : 10000);
        for (size_t i = 0; i < warm; ++i)
            m.insert(typename Map::value_type((int)i, (int)(i * 3)));

        for (size_t i = 0; i < ops; ++i)
        {
            const int k = (int)rng.index(kr);
            const int v = rng.next_int();

            unsigned r = rng.next_u32() % 6;
            if (r <= 2)
            {
                // erase by key
                (void)m.erase(k);
            }
            else if (r == 3)
            {
                // insert
                m.insert(typename Map::value_type(k, v));
            }
            else if (r == 4)
            {
                // operator[]
                m[k] = v;
            }
            else
            {
                // find
                (void)m.find(k);
            }
        }
    }
};

void test_map_stress_erase()
{
    typedef ft::map<int, int> Map;

    const u64    seed      = env_u64("STRESS_SEED", 11ULL);
    const size_t ops       = env_sz("STRESS_OPS", 200000);
    const size_t key_range = env_sz("STRESS_KEY_RANGE", 200000);

    Map m;
    MapCtx<Map> ctx;
    ctx.m = &m;
    ctx.key_range = key_range;

    run_stress_case("map_stress_erase", ctx, MapEraseBody(), seed, ops);
}
