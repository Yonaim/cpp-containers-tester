#ifndef TEST_STRESS_UTIL_H
#define TEST_STRESS_UTIL_H

// Stress-test utilities (C++98).
// Assumes including .cpp has already included "test_namespace.h" before this header,
// so that ft::pair and containers are visible (ft = std in STD_MODE).

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#if !defined(_WIN32)
    #include <time.h>     // clock_gettime, timespec (POSIX)
    #include <sys/time.h> // gettimeofday fallback
#endif

typedef unsigned long long u64;

// ---------------- Random Number Generator(RNG): xorshift64* ------------------
struct StressRng
{
    u64 s;
    explicit StressRng(u64 seed) : s(seed ? seed : 88172645463325252ULL) {}

    u64 next_u64()
    {
        u64 x = s;
        x ^= x >> 12;
        x ^= x << 25;
        x ^= x >> 27;
        s = x;
        return x * 2685821657736338717ULL;
    }

    unsigned next_u32() { return (unsigned)(next_u64() >> 32); }

    size_t index(size_t bound)
    {
        if (bound == 0)
            return 0;
        return (size_t)(next_u64() % (u64)bound);
    }

    int next_int() { return (int)(next_u32() & 0x7fffffffU); }
};

// ---------------- Dual Timer (wall + cpu), ms ----------------
struct StressTimer
{
    std::clock_t cpu0;

#if defined(_WIN32)
    void   start() { cpu0 = std::clock(); }
    double wall_ms() const
    {
        // Fallback: CPU time (no monotonic wall-clock in portable C++98)
        return (double)(std::clock() - cpu0) * 1000.0 / (double)CLOCKS_PER_SEC;
    }
#else
    #if defined(CLOCK_MONOTONIC)
    timespec wall0;
    void     start()
    {
        cpu0 = std::clock();
        clock_gettime(CLOCK_MONOTONIC, &wall0);
    }

    double wall_ms() const
    {
        timespec now;
        clock_gettime(CLOCK_MONOTONIC, &now);
        long sec = (long)(now.tv_sec - wall0.tv_sec);
        long nsec = (long)(now.tv_nsec - wall0.tv_nsec);
        if (nsec < 0)
        {
            nsec += 1000000000L;
            sec -= 1;
        }
        return (double)sec * 1000.0 + (double)nsec / 1e6;
    }
    #else
    timeval wall0;
    void    start()
    {
        cpu0 = std::clock();
        gettimeofday(&wall0, 0);
    }

    double wall_ms() const
    {
        timeval now;
        gettimeofday(&now, 0);
        long sec = (long)(now.tv_sec - wall0.tv_sec);
        long usec = (long)(now.tv_usec - wall0.tv_usec);
        if (usec < 0)
        {
            usec += 1000000L;
            sec -= 1;
        }
        return (double)sec * 1000.0 + (double)usec / 1000.0;
    }
    #endif
#endif

    double cpu_ms() const
    {
        return (double)(std::clock() - cpu0) * 1000.0 / (double)CLOCKS_PER_SEC;
    }

    // Backward-compat: ms() returns wall-clock in ms.
    double ms() const { return wall_ms(); }
};

// ---------------- FNV-1a-ish mix ----------------
static inline u64 mix_u64(u64 h, u64 x)
{
    const u64 PRIME = 1099511628211ULL;
    h ^= x;
    h *= PRIME;
    return h;
}

static inline u64 hash_int(u64 h, int x)
{
    u64 v = (u64)(unsigned)x;
    // cheap extra mixing
    v ^= (v << 21);
    v ^= (v >> 7);
    v ^= (v << 4);
    return mix_u64(h, v);
}

static inline u64 hash_sz(u64 h, size_t x) { return mix_u64(h, (u64)x); }

// ---------------- env helpers ----------------
static inline u64 parse_u64(const char *s, u64 defv)
{
    if (!s || !*s)
        return defv;
    char *end = 0;
#if defined(__cplusplus) && (__cplusplus >= 201103L)
    unsigned long long v = std::strtoull(s, &end, 10);
#else
    // In practice, libstdc++ provides strtoull even in -std=c++98; keep a fallback anyway.
    unsigned long long v = (unsigned long long)std::strtoul(s, &end, 10);
#endif
    if (end == s)
        return defv;
    return (u64)v;
}

static inline size_t parse_sz(const char *s, size_t defv)
{
    if (!s || !*s)
        return defv;
    char         *end = 0;
    unsigned long v = std::strtoul(s, &end, 10);
    if (end == s)
        return defv;
    return (size_t)v;
}

static inline size_t env_sz(const char *name, size_t defv)
{
    const char *p = std::getenv(name);
    return parse_sz(p, defv);
}

static inline u64 env_u64(const char *name, u64 defv)
{
    const char *p = std::getenv(name);
    return parse_u64(p, defv);
}

// ---------------- stress printing helpers ----------------
static inline void print_stress_kv(const char *k, unsigned long long v)
{
    std::cout << " " << k << "=" << v;
}
static inline void print_stress_kv_d(const char *k, double v) { std::cout << " " << k << "=" << v; }

// ---------------- generic-ish value hashing ----------------
static inline u64 stress_hash_value(u64 h, int x) { return hash_int(h, x); }
static inline u64 stress_hash_value(u64 h, unsigned x) { return mix_u64(h, (u64)x); }
static inline u64 stress_hash_value(u64 h, long x) { return mix_u64(h, (u64)x); }
static inline u64 stress_hash_value(u64 h, unsigned long x) { return mix_u64(h, (u64)x); }

static inline u64 stress_hash_value(u64 h, const std::string &s)
{
    for (size_t i = 0; i < s.size(); ++i)
        h = mix_u64(h, (unsigned char)s[i]);
    return h;
}

// ft::pair / std::pair (ft is set in test_namespace.h)
template <class A, class B>
static inline u64 stress_hash_value(u64 h, const ft::pair<A, B> &p)
{
    h = stress_hash_value(h, p.first);
    h = stress_hash_value(h, p.second);
    return h;
}

// ---------------- range checksum ----------------
template <class It>
u64 checksum_range(It first, It last)
{
    u64    h = 1469598103934665603ULL;
    size_t i = 0;
    for (; first != last; ++first, ++i)
    {
        h = stress_hash_value(h, *first);
        h = hash_sz(h, i); // order sensitivity (vector), harmless for map as it has fixed order
    }
    h = hash_sz(h, i);
    return h;
}

// ---------------- tiny algorithm helpers (no dependency on ft::equal/lexicographical_compare)
// ----------------
template <class It1, class It2>
bool stress_equal(It1 f1, It1 l1, It2 f2)
{
    for (; f1 != l1; ++f1, ++f2)
        if (!(*f1 == *f2))
            return false;
    return true;
}

template <class It1, class It2>
bool stress_lexicographical_compare(It1 f1, It1 l1, It2 f2, It2 l2)
{
    for (; (f1 != l1) && (f2 != l2); ++f1, ++f2)
    {
        if (*f1 < *f2)
            return true;
        if (*f2 < *f1)
            return false;
    }
    return (f1 == l1) && (f2 != l2);
}

// ---------------- Common runner (Approach #2: template + functor) ----------------
struct StressRunStats
{
    double wall_ms;
    double cpu_ms;
    u64    checksum;
    size_t size;
};

template <class Ctx, class Body>
StressRunStats run_stress_case(const char *name, Ctx &ctx, const Body &body, u64 seed, size_t ops)
{
    StressRng   rng(seed);
    StressTimer tm;
    tm.start();

    body(ctx, rng, ops);

    StressRunStats st;
    st.wall_ms = tm.wall_ms();
    st.cpu_ms = tm.cpu_ms();
    st.checksum = ctx.checksum();
    st.size = ctx.size();

    std::cout << name;
    print_stress_kv("ops", (unsigned long long)ops);
    print_stress_kv("seed", (unsigned long long)seed);
    print_stress_kv("size", (unsigned long long)st.size);
    print_stress_kv("checksum", (unsigned long long)st.checksum);
    print_stress_kv_d("wall_ms", st.wall_ms);
    print_stress_kv_d("cpu_ms", st.cpu_ms);
    std::cout << "\n";

    return st;
}

// ---------------- Context helpers (vector/map/stack) ----------------
template <class Vec>
struct VectorCtx
{
    Vec   *v;
    size_t max_size;

    u64    checksum() const { return checksum_range(v->begin(), v->end()); }
    size_t size() const { return (size_t)v->size(); }
};

template <class Map>
struct MapCtx
{
    Map   *m;
    size_t key_range;

    u64    checksum() const { return checksum_range(m->begin(), m->end()); }
    size_t size() const { return (size_t)m->size(); }
};

// For stack: keep a mirror sequence for checksum (since stack has no iterators).
template <class Stack, class MirrorVec>
struct StackCtx
{
    Stack    *s;
    MirrorVec mirror; // push/pop mirror

    u64    checksum() const { return checksum_range(mirror.begin(), mirror.end()); }
    size_t size() const { return (size_t)mirror.size(); }
};

#endif // TEST_STRESS_UTIL_H
