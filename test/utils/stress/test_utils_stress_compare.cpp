#include "test_print.h"
#include "test_namespace.h"
#include "test_stress_util.h"

#include <vector>

// Env knobs:
//  STRESS_SEED (u64)   default: 31
//  STRESS_OPS (size_t) default: 200000
//
// Builds random integer sequences and stresses comparisons:
//  - equality over ranges
//  - lexicographical compare over ranges
// Results are folded into a checksum to allow STD vs FT diffing.

struct CompareCtx
{
    u64 h;
    CompareCtx() : h(1469598103934665603ULL) {}

    u64 checksum() const { return h; }
    size_t size() const { return 0; }
};

static void make_seq(std::vector<int> &out, StressRng &rng, size_t n)
{
    out.clear();
    out.reserve(n);
    for (size_t i = 0; i < n; ++i)
        out.push_back(rng.next_int());
}

struct CompareBody
{
    void operator()(CompareCtx &ctx, StressRng &rng, size_t ops) const
    {
        std::vector<int> a, b;

        for (size_t i = 0; i < ops; ++i)
        {
            size_t na = (rng.next_u32() % 32);
            size_t nb = (rng.next_u32() % 32);

            make_seq(a, rng, na);
            make_seq(b, rng, nb);

            bool eq = stress_equal(a.begin(), a.end(), b.begin()); // only valid if same length
            if (a.size() != b.size())
                eq = false;

            bool lc = stress_lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());

            ctx.h = mix_u64(ctx.h, (u64)eq);
            ctx.h = mix_u64(ctx.h, (u64)lc);
            ctx.h = mix_u64(ctx.h, (u64)a.size());
            ctx.h = mix_u64(ctx.h, (u64)b.size());

            // include some content to make it harder to "accidentally" match
            ctx.h = checksum_range(a.begin(), a.end()) ^ ctx.h;
            ctx.h = checksum_range(b.begin(), b.end()) ^ (ctx.h << 1);
        }
    }
};

void test_utils_stress_compare()
{
    const u64    seed = env_u64("STRESS_SEED", 31ULL);
    const size_t ops  = env_sz("STRESS_OPS", 200000);

    CompareCtx ctx;
    run_stress_case("utils_stress_compare", ctx, CompareBody(), seed, ops);
}
