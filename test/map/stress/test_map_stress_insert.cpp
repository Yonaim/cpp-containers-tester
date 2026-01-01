#include "test_print.h"
#include "test_namespace.h"
#include "test_stress_util.h"

// Env knobs:
//  STRESS_SEED (u64)           default: 10
//  STRESS_OPS (size_t)         default: 200000
//  STRESS_KEY_RANGE (size_t)   default: 200000
//
// Focus: insert (by insert + operator[]), plus some finds to exercise lookup paths.

struct MapInsertBody
{
    template <class Map>
    void operator()(MapCtx<Map> &ctx, StressRng &rng, size_t ops) const
    {
        Map &m = *ctx.m;
        const size_t kr = (ctx.key_range ? ctx.key_range : 1);

        for (size_t i = 0; i < ops; ++i)
        {
            const int k = (int)rng.index(kr);
            const int v = rng.next_int();

            unsigned r = rng.next_u32() % 5;
            if (r == 0)
            {
                // insert value_type
                m.insert(typename Map::value_type(k, v));
            }
            else if (r == 1)
            {
                // hint insert (use begin() as a stable hint)
                m.insert(m.begin(), typename Map::value_type(k, v));
            }
            else if (r == 2)
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

void test_map_stress_insert()
{
    typedef ft::map<int, int> Map;

    const u64    seed      = env_u64("STRESS_SEED", 10ULL);
    const size_t ops       = env_sz("STRESS_OPS", 200000);
    const size_t key_range = env_sz("STRESS_KEY_RANGE", 200000);

    Map m;
    MapCtx<Map> ctx;
    ctx.m = &m;
    ctx.key_range = key_range;

    run_stress_case("map_stress_insert", ctx, MapInsertBody(), seed, ops);
}
