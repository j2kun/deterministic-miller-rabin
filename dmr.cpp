#include "dmr.h"

#include <cstdint>

// Bases to test. Using the first 12 prime bases makes the test deterministic
// for all 64-bit integers. See https://oeis.org/A014233.
int64_t bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

inline int countTrailingZeros(uint64_t n) {
  if (n == 0)
    return 64;
  return __builtin_ctzll(n);
}

bool isPrime(int64_t n) {
  if (n < 2)
    return false;
  if (n < 4)
    return true;
  if (!(n & 1))
    return false;

  int64_t d = n - 1;
  unsigned s = countTrailingZeros(d);
  d = d >> s;

  for (uint64_t a : bases) {
    if (n <= a)
      break;
    int64_t x = modularExponentiation(a, d, n);
    if (x == 1 || x == n - 1)
      continue;
    bool composite = true;
    for (unsigned r = 1; r < s; ++r) {
      x = (x * x) % n;
      if (x == n - 1) {
        composite = false;
        break;
      }
    }
    if (composite)
      return false;
  }
  return true;
}

int64_t modularExponentiation(int64_t base, int64_t exponent, int64_t modulus) {
  int64_t res = 1;
  int64_t b = base % modulus;
  int64_t e = exponent;

  while (e > 0) {
    if (e & 1) {
      res = (res * b) % modulus;
    }
    b = (b * b) % modulus;
    e >>= 1;
  }
  return res;
}
