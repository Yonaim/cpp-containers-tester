#include "test_print.h"
#include "test_namespace.h"
#include "test_stress_util.h"

// Classic MutantStack test (iterating through the underlying container).
// Assumes ft::stack follows std::stack: protected member 'c' and container_type typedef.
//
// Env knobs:
//  STRESS_SEED (u64) default: 200 (used only for logging)

template <typename T>
class MutantStack : public ft::stack<T>
{
  public:
    MutantStack() {}
    MutantStack(const MutantStack &src) { *this = src; }
    MutantStack &operator=(const MutantStack &rhs)
    {
        this->c = rhs.c;
        return *this;
    }
    ~MutantStack() {}

    typedef typename ft::stack<T>::container_type::iterator iterator;
    iterator begin() { return this->c.begin(); }
    iterator end() { return this->c.end(); }
};

struct MutantStackCtx
{
    u64 h;
    MutantStackCtx() : h(1469598103934665603ULL) {}
    u64 checksum() const { return h; }
    size_t size() const { return 26; }
};

struct MutantStackBody
{
    void operator()(MutantStackCtx &ctx, StressRng &/*rng*/, size_t /*ops*/) const
    {
        MutantStack<char> st;
        for (char c = 'a'; c <= 'z'; ++c)
            st.push(c);

        // iterate through underlying container
        for (MutantStack<char>::iterator it = st.begin(); it != st.end(); ++it)
        {
            ctx.h = mix_u64(ctx.h, (u64)(unsigned char)(*it));
        }

        // sanity: size should be 26
        if ((size_t)st.size() != 26)
        {
            std::cerr << "Error: mutant stack size mismatch\n";
            std::abort();
        }
    }
};

void test_stack_stress_mutant_iter()
{
    const u64 seed = env_u64("STRESS_SEED", 200ULL);
    const size_t ops = env_sz("STRESS_OPS", 1);

    MutantStackCtx ctx;
    StressRng dummy(seed);
    (void)dummy;

    run_stress_case("stack_mutant_iter", ctx, MutantStackBody(), seed, ops);
}
