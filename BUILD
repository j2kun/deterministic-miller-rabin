load("@rules_cc//cc:cc_binary.bzl", "cc_binary")
load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("@rules_cc//cc:cc_test.bzl", "cc_test")

cc_library(
    name = "dmr",
    srcs = ["dmr.cpp"],
    hdrs = ["dmr.h"],
)


cc_test(
    name = "dmr_test",
    srcs = ["dmr_test.cpp"],
    deps = [
        ":dmr",
        "@googletest//:gtest_main",
    ],
)


cc_binary(
    name = "dmr_benchmark",
    srcs = ["dmr_benchmark.cpp"],
    deps = [
        ":dmr",
        "@google_benchmark//:benchmark",
    ],
)

cc_binary(
    name = "benchmark_32bit",
    srcs = ["benchmark_32bit.cpp"],
    deps = [
        ":dmr",
        "@google_benchmark//:benchmark",
    ],
)
