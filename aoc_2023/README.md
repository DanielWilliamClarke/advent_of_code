# AdventOfCode2023 🎄

## Install dependencies

### MacOS

- [ ] Install XCode from the Appstore

```bash
    # for the first time you will need agree to the XCode license
    xcode-select --install 
    sudo xcode-select --switch /Applications/Xcode.app     
    sudo xcodebuild -license accept

    brew install bazel
```

## Build, test and run

### With Bazel

```bash
# Build AOC 2023 executable
bazel build src/aoc-2023

# Run AOC 2023 tests
bazel test --test_output=all //test:aoc-2023

# Build and Run AOC 2023 executable
bazel run src/aoc-2023
```
