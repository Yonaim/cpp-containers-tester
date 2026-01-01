#include "test_print.h"
#include "test_namespace.h"
#include "test_stress_util.h"

// Env knobs:
//  STRESS_SEED (u64)   default: 30
//  STRESS_OPS (size_t) default: 300000
//
// Stresses ft::pair construction and relational operators.
// Produces a deterministic checksum of comparison outcomes.

struct PairCtx
{
    u64 h;
    PairCtx() : h(1469598103934665603ULL) {}

    u64 checksum() const { return h; }
    size_t size() const { return 0; } // not meaningful here
};

struct PairBody
{
    void operator()(PairCtx &ctx, StressRng &rng, size_t ops) const
    {
        for (size_t i = 0; i < ops; ++i)
        {
            int a1 = rng.next_int();
            int b1 = rng.next_int();
            int a2 = rng.next_int();
            int b2 = rng.next_int();

            ft::pair<int, int> p1(a1, b1);
            ft::pair<int, int> p2(a2, b2);

            // fold boolean results into checksum
            ctx.h = mix_u64(ctx.h, (u64)(p1 == p2));
            ctx.h = mix_u64(ctx.h, (u64)(p1 != p2));
            ctx.h = mix_u64(ctx.h, (u64)(p1 <  p2));
            ctx.h = mix_u64(ctx.h, (u64)(p1 <= p2));
            ctx.h = mix_u64(ctx.h, (u64)(p1 >  p2));
            ctx.h = mix_u64(ctx.h, (u64)(p1 >= p2));

            // also hash the pairs directly
            ctx.h = stress_hash_value(ctx.h, p1);
            ctx.h = stress_hash_value(ctx.h, p2);
        }
    }
};

void test_utils_stress_pair()
{
    const u64    seed = env_u64("STRESS_SEED", 30ULL);
    const size_t ops  = env_sz("STRESS_OPS", 300000);

    PairCtx ctx;
    run_stress_case("utils_stress_pair", ctx, PairBody(), seed, ops);
}
