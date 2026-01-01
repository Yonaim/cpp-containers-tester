#include "test_namespace.h"
#include "test_print.h"
#include "test_stress_util.h"

// Env knobs:
//  STRESS_SEED (u64)         default: 3
//  STRESS_OPS (size_t)       default: 80000
//  STRESS_MAX_SIZE (size_t)  default: 50000
//
// This builds up to max_size and then performs random range erases.

struct VectorEraseBody
{
    template <class Vec>
    void operator()(VectorCtx<Vec> &ctx, StressRng &rng, size_t ops) const
    {
        Vec &v = *ctx.v;

        // Warm-up: fill some elements
        const size_t warm = (ctx.max_size ? (ctx.max_size / 2) : 10000);
        for (size_t i = 0; i < warm; ++i)
            v.push_back(rng.next_int());

        for (size_t i = 0; i < ops; ++i)
        {
            unsigned r = rng.next_u32();

            if ((r & 3) != 0)
            {
                // keep adding to create erase work
                if (ctx.max_size == 0 || (size_t)v.size() < ctx.max_size)
                    v.push_back(rng.next_int());
            }
            else if (!v.empty())
            {
                // erase range [a, b)
                size_t n = (size_t)v.size();
                size_t a = rng.index(n);
                size_t b = rng.index(n);
                if (a > b)
                {
                    size_t t = a;
                    a = b;
                    b = t;
                }
                if (a == b)
                    b = (b < n ? b + 1 : b);
                v.erase(v.begin() + (typename Vec::difference_type)a,
                        v.begin() + (typename Vec::difference_type)b);
            }
        }
    }
};

void test_vector_stress_erase()
{
    typedef ft::vector<int> Vec;

    const u64    seed = env_u64("STRESS_SEED", 3ULL);
    const size_t ops = env_sz("STRESS_OPS", 80000);
    const size_t max_size = env_sz("STRESS_MAX_SIZE", 50000);

    Vec            v;
    VectorCtx<Vec> ctx;
    ctx.v = &v;
    ctx.max_size = max_size;

    run_stress_case("vector_stress_erase", ctx, VectorEraseBody(), seed, ops);
}
