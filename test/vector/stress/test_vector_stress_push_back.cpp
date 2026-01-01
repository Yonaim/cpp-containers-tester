#include "test_namespace.h"
#include "test_print.h"
#include "test_stress_util.h"

// Env knobs (optional):
//  STRESS_SEED (u64)         default: 1
//  STRESS_OPS (size_t)       default: 200000
//  STRESS_MAX_SIZE (size_t)  default: 50000

struct VectorPushPopBody
{
    template <class Vec>
    void operator()(VectorCtx<Vec> &ctx, StressRng &rng, size_t ops) const
    {
        Vec &v = *ctx.v;

        for (size_t i = 0; i < ops; ++i)
        {
            unsigned r = rng.next_u32();
            if (v.empty() || (r & 1))
            {
                if (ctx.max_size == 0 || (size_t)v.size() < ctx.max_size)
                    v.push_back(rng.next_int());
            }
            else
            {
                v.pop_back();
            }
        }
    }
};

void test_vector_stress_push_back()
{
    typedef ft::vector<int> Vec;

    const u64    seed = env_u64("STRESS_SEED", 1ULL);
    const size_t ops = env_sz("STRESS_OPS", 200000);
    const size_t max_size = env_sz("STRESS_MAX_SIZE", 50000);

    Vec            v;
    VectorCtx<Vec> ctx;
    ctx.v = &v;
    ctx.max_size = max_size;

    run_stress_case("vector_stress_push_back", ctx, VectorPushPopBody(), seed, ops);
}
