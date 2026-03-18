#include "dmr.h"

#include <benchmark/benchmark.h>

static void BM_IsPrime_LargePrime(benchmark::State& state) {
  // 2^61 - 1 (Mersenne prime)
  int64_t n = 2305843009213693951LL;
  for (auto _ : state) {
    benchmark::DoNotOptimize(isPrime(n));
  }
}
BENCHMARK(BM_IsPrime_LargePrime);

static void BM_IsPrime_LargeComposite(benchmark::State& state) {
  // (2^31 - 1) * (2^13 - 1)
  int64_t n = 17592184930305LL;
  for (auto _ : state) {
    benchmark::DoNotOptimize(isPrime(n));
  }
}
BENCHMARK(BM_IsPrime_LargeComposite);

static void BM_IsPrime_Range(benchmark::State& state) {
  int64_t start_num = state.range(0);
  for (auto _ : state) {
    for (int64_t i = 0; i < 100; ++i) {
      benchmark::DoNotOptimize(isPrime(start_num + i));
    }
  }
}
BENCHMARK(BM_IsPrime_Range)->Arg(1000)->Arg(1000000)->Arg(1000000000);

BENCHMARK_MAIN();
