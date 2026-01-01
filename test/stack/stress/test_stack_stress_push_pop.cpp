#include "test_print.h"
#include "test_namespace.h"
#include "test_stress_util.h"

#include <vector>

// Env knobs:
//  STRESS_SEED (u64)       default: 20
//  STRESS_OPS (size_t)     default: 200000
//  STRESS_MAX_SIZE (size_t)default: 50000
//
// Uses a mirror std::vector<int> to checksum contents because stack has no iterators.

struct StackPushPopBody
{
    template <class Stack, class MirrorVec>
    void operator()(StackCtx<Stack, MirrorVec> &ctx, StressRng &rng, size_t ops) const
    {
        Stack &s = *ctx.s;

        const size_t max_size = env_sz("STRESS_MAX_SIZE", 50000);

        for (size_t i = 0; i < ops; ++i)
        {
            unsigned r = rng.next_u32();
            if (ctx.mirror.empty() || (r & 1))
            {
                if (max_size == 0 || ctx.mirror.size() < max_size)
                {
                    int x = rng.next_int();
                    s.push(x);
                    ctx.mirror.push_back(x);
                }
            }
            else
            {
                // verify top matches mirror
                int a = s.top();
                int b = ctx.mirror.back();
                if (!(a == b))
                {
                    std::cout << "stack_mismatch top=" << a << " mirror=" << b << "\n";
                    std::abort();
                }
                s.pop();
                ctx.mirror.pop_back();
            }

            // occasional top() reads
            if (!ctx.mirror.empty() && ((r & 7) == 0))
            {
                int a = s.top();
                int b = ctx.mirror.back();
                if (!(a == b))
                {
                    std::cout << "stack_mismatch top=" << a << " mirror=" << b << "\n";
                    std::abort();
                }
            }
        }

        // final consistency check
        if ((size_t)s.size() != ctx.mirror.size())
        {
            std::cout << "stack_size_mismatch stack=" << (unsigned long long)s.size()
                      << " mirror=" << (unsigned long long)ctx.mirror.size() << "\n";
            std::abort();
        }
    }
};

void test_stack_stress_push_pop()
{
    typedef ft::stack<int> Stack;
    typedef std::vector<int> Mirror;

    const u64    seed = env_u64("STRESS_SEED", 20ULL);
    const size_t ops  = env_sz("STRESS_OPS", 200000);

    Stack s;
    StackCtx<Stack, Mirror> ctx;
    ctx.s = &s;

    run_stress_case("stack_stress_push_pop", ctx, StackPushPopBody(), seed, ops);
}
