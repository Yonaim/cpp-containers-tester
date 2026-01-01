#include "test_namespace.h"
#include "test_print.h"
#include "test_stress_util.h"

// A scaled version of the classic Ecole42 "MAX_RAM/Buffer" vector stress.
// It exercises:
//  - many push_backs of a large POD (Buffer)
//  - random indexed writes
//  - swap-with-empty to free memory
//  - at() throwing on empty container
//
// Env knobs:
//  STRESS_SEED (u64)          default: 100
//  STRESS_RAM_MB (size_t)     default: 128   (target allocation size)
//  STRESS_COUNT (size_t)      default: 0     (if non-zero, overrides RAM_MB-derived count)
//  STRESS_AT_TRIES (size_t)   default: 1000

#define BUFFER_SIZE 4096

struct Buffer
{
    int  idx;
    char buff[BUFFER_SIZE];
};

struct VectorBufferCtx
{
    ft::vector<Buffer> *v;
    u64                 h; // record work done (before swap)
    VectorBufferCtx() : v(0), h(1469598103934665603ULL) {}

    u64    checksum() const { return h; }
    size_t size() const { return (size_t)v->size(); }
};

struct VectorBufferBody
{
    void operator()(VectorBufferCtx &ctx, StressRng &rng, size_t /*ops*/) const
    {
        ft::vector<Buffer> &vb = *ctx.v;

        const u64 seed = env_u64("STRESS_SEED", 100ULL);
        (void)seed;
        const size_t ram_mb = env_sz("STRESS_RAM_MB", 128);
        const size_t overrideN = env_sz("STRESS_COUNT", 0);
        const size_t at_tries = env_sz("STRESS_AT_TRIES", 1000);

        // Derive count from RAM target unless overridden.
        const size_t bytes = (size_t)ram_mb * (size_t)1024 * (size_t)1024;
        size_t       count = bytes / sizeof(Buffer);
        if (overrideN != 0)
            count = overrideN;
        if (count == 0)
            count = 1;

        // 1) allocate via push_back
        vb.clear();
#if !defined(FT_VECTOR_NO_RESERVE)
        vb.reserve(count);
#endif
        for (size_t i = 0; i < count; ++i)
            vb.push_back(Buffer());

        // 2) random writes
        for (size_t i = 0; i < count; ++i)
        {
            size_t idx = rng.index(count);
            vb[idx].idx = 5;
        }

        // 3) capture a checksum of work (only idx fields, not the whole 4KB payload)
        u64 h = 1469598103934665603ULL;
        for (size_t i = 0; i < vb.size(); ++i)
            h = hash_int(h, vb[i].idx);
        h = hash_sz(h, vb.size());
        ctx.h = h;

        // 4) free memory by swapping with empty (classic trick)
        ft::vector<Buffer>().swap(vb);

        // 5) at() must throw on empty
        bool threw = false;
        try
        {
            for (size_t i = 0; i < at_tries; ++i)
            {
                size_t idx = rng.index(count);
                (void)vb.at(idx);
                // If we get here, at() failed to throw on an empty vector.
                std::cerr << "Error: vector::at() did not throw on empty vector\n";
                std::abort();
            }
        }
        catch (const std::exception &e)
        {
            (void)e;
            threw = true;
        }
        if (!threw)
        {
            std::cerr << "Error: expected an exception from vector::at()\n";
            std::abort();
        }
    }
};

void test_vector_stress_buffer_ram()
{
    typedef ft::vector<Buffer> VecBuf;

    const u64    seed = env_u64("STRESS_SEED", 100ULL);
    const size_t ops = env_sz("STRESS_OPS", 1); // unused; keep compatibility

    VecBuf          vb;
    VectorBufferCtx ctx;
    ctx.v = &vb;

    run_stress_case("vector_stress_buffer_ram", ctx, VectorBufferBody(), seed, ops);
}
