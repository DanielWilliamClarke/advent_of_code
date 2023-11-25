# AdventOfCode2023 🎄

## Install dependencies

```bash
    brew install bazel
    brew install make
    brew install cmake
    brew install conan@1 # conan2 is a bit of a nightmare to deal with
    brew install llvm
```

## Build, test and run

```bash
# Debug
    make install_debug
    make build_debug
    make runtests_debug
    make run_debug

# Release
    make install_release
    make build_release
    make run_release
```


# Bazel 

```
bazel build --cxxopt=-std=c++20 src/aoc-2023
bazel run --cxxopt=-std=c++20 src/aoc-2023
bazel test --cxxopt=-std=c++20 --test_output=all //test:aoc-2023-test
```