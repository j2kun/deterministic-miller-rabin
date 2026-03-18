#include "dmr.h"

struct Montgomery {
    uint64_t n;
    uint64_t n_inv;
    uint64_t r2;

    Montgomery(uint64_t mod) : n(mod) {
        // Modular inverse: n * n_inv ≡ 1 (mod 2^64)
        // We actually need the negative inverse for the REDC algorithm.
        uint64_t inv = n;
        for (int i = 0; i < 5; ++i) inv *= 2 - n * inv;
        n_inv = inv;

        // Correctly calculate r2 = (2^64)^2 mod n
        // We use __uint128_t to safely perform (2^64 % n)
        uint64_t r = static_cast<uint64_t>((__uint128_t(1) << 64) % n);
        r2 = static_cast<uint64_t>((static_cast<__uint128_t>(r) * r) % n);
    }

    uint64_t reduce(__uint128_t T) const {
        uint64_t m = static_cast<uint64_t>(T) * n_inv;
        // The standard REDC algorithm: (T + m*n) / R
        // We use the property that (T + m*n) is always divisible by 2^64
        __uint128_t mn = static_cast<__uint128_t>(m) * n;
        __uint128_t summed = T + mn;
        uint64_t res = static_cast<uint64_t>(summed >> 64);

        if (res >= n) res -= n;
        return res;
    }

    uint64_t transform(uint64_t x) const {
        return reduce(static_cast<__uint128_t>(x) * r2);
    }
};

bool isPrime(int64_t n_signed) {
    uint64_t n = static_cast<uint64_t>(n_signed);
    // Basic cases
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    if (n < 4) return true;

    static const uint64_t bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    uint64_t d = n - 1;
    int s = __builtin_ctzll(d);
    d >>= s;

    Montgomery m_ctx(n);
    uint64_t one_mont = m_ctx.transform(1);
    uint64_t n_minus_one_mont = m_ctx.transform(n - 1);

    for (uint64_t a : bases) {
        if (n <= a) break;

        // Montgomery Modular Exponentiation
        uint64_t a_mont = m_ctx.transform(a);
        uint64_t x_mont = one_mont;
        uint64_t e = d;
        while (e > 0) {
            if (e & 1) x_mont = m_ctx.reduce(static_cast<__uint128_t>(x_mont) * a_mont);
            a_mont = m_ctx.reduce(static_cast<__uint128_t>(a_mont) * a_mont);
            e >>= 1;
        }

        if (x_mont == one_mont || x_mont == n_minus_one_mont) continue;

        bool composite = true;
        for (int r = 1; r < s; ++r) {
            x_mont = m_ctx.reduce(static_cast<__uint128_t>(x_mont) * x_mont);
            if (x_mont == n_minus_one_mont) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}
