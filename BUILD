cc_library(
    name = "myVector-definition",
    hdrs = ["myVector.h"]
)

cc_test(
    name = "myVector-test",
    srcs = ["myVector_test.cc"],
    deps = [
        "@com_google_googletest//:gtest_main",
        ":myVector-definition"
    ]
)
