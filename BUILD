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

