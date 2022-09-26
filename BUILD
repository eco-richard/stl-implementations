cc_library(
    name = "MyVector-definition",
    hdrs = ["MyVector.h"]
)

cc_test(
    name = "MyVector-test",
    srcs = ["test/MyVector_test.cc"],
    size = "small",
    copts = ["-std=c++17 -w"],
    deps = [
        "@com_google_googletest//:gtest_main",
        ":MyVector-definition"
    ]
)
