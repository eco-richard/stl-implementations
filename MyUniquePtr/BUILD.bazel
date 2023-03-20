cc_library(
  name = "MyUniquePtr-definition",
  hdrs = ["UniquePtr.h"],
)

cc_test(
  name = "MyUniquePtr-test",
  srcs = ["test/MyUniquePtr_test.cc"],
  size = "small",
  copts = ["--std=c++17 -w"],
  deps = [
    "@com_google_googletest//:gtest_main",
    ":MyUniquePtr-definition"
  ]
)
