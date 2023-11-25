# AdventOfCode2023 🎄

## Install dependencies

```bash
    brew install bazel
```

## Build, test and run

### With Bazel

```bash
bazel build --cxxopt=-std=c++20 src/aoc-2023
bazel run --cxxopt=-std=c++20 src/aoc-2023
bazel test --cxxopt=-std=c++20 --test_output=all //test:aoc-2023-test
```
