#include <benchmark/benchmark.h>
#include <cstdint>
#include <limits>
#include "dmr.h"

static void BM_PrimeTest_All32Bit(benchmark::State& state) {
    uint32_t count = 0;
    for (auto _ : state) {
        // Warning: This loop runs 4,294,967,295 times.
        // It will take a few minutes to complete one iteration.
        for (uint64_t i = 0; i <= std::numeric_limits<uint32_t>::max(); ++i) {
            if (isPrime(static_cast<int64_t>(i))) {
                count++;
            }
        }
        benchmark::DoNotOptimize(count);
    }
    // Record the number of 32-bit integers processed per second
    state.SetItemsProcessed(state.iterations() * 4294967296ULL);
}

// Set a long timeout because this is a heavy test
BENCHMARK(BM_PrimeTest_All32Bit)->Unit(benchmark::kSecond)->Iterations(1);

BENCHMARK_MAIN();
