#include "test_namespace.h"
#include "test_print.h"
#include "test_stress_util.h"

// Env knobs:
//  STRESS_SEED (u64)         default: 2
//  STRESS_OPS (size_t)       default: 120000
//  STRESS_MAX_SIZE (size_t)  default: 20000
//
// This focuses on insert at random positions, with occasional erase to keep size bounded.

struct VectorInsertBody
{
    template <class Vec>
    void operator()(VectorCtx<Vec> &ctx, StressRng &rng, size_t ops) const
    {
        Vec &v = *ctx.v;

        for (size_t i = 0; i < ops; ++i)
        {
            const unsigned r = rng.next_u32();
            const bool     do_insert = (v.empty() || (r % 4 != 0)); // ~75% insert

            if (do_insert)
            {
                if (ctx.max_size == 0 || (size_t)v.size() < ctx.max_size)
                {
                    const size_t pos = rng.index((size_t)v.size() + 1);
                    v.insert(v.begin() + (typename Vec::difference_type)pos, rng.next_int());
                }
            }
            else
            {
                // erase single element
                const size_t pos = rng.index((size_t)v.size());
                v.erase(v.begin() + (typename Vec::difference_type)pos);
            }
        }
    }
};

void test_vector_stress_insert()
{
    typedef ft::vector<int> Vec;

    const u64    seed = env_u64("STRESS_SEED", 2ULL);
    const size_t ops = env_sz("STRESS_OPS", 120000);
    const size_t max_size = env_sz("STRESS_MAX_SIZE", 20000);

    Vec            v;
    VectorCtx<Vec> ctx;
    ctx.v = &v;
    ctx.max_size = max_size;

    run_stress_case("vector_stress_insert", ctx, VectorInsertBody(), seed, ops);
}
