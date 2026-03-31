// Deterministic Miller-Rabin primality test for limited bit-widths using
// https://oeis.org/A014233

#include <cstdint>

// Check for primality, works for a 32-bit input.
bool isPrime(int64_t n);

int64_t modularExponentiation(int64_t base, int64_t exponent, int64_t modulus);
