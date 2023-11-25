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
    brew install buildifier
```

## Build, test and run

### With Bazel

```bash
# Build AOC 2023 executable with Debug
bazel build -c dbg main/aoc-2023
# You now should be able to debug the exe

# Build AOC 2023 executable
bazel build main/aoc-2023

# Run AOC 2023 tests
bazel test --test_output=all //test:aoc-2023

# Build and Run AOC 2023 executable
bazel run main/aoc-2023
```

## Resources

- <https://bazel.build/start/cpp>
- <https://bazel.build/tutorials/cpp-use-cases>
- <https://google.github.io/googletest/quickstart-bazel.html>
- <https://apple.stackexchange.com/questions/175069/how-to-accept-xcode-license>
- <https://marketplace.visualstudio.com/items?itemName=BazelBuild.vscode-bazel>
- <https://github.com/bazelbuild/examples/blob/main/cpp-tutorial/stage3/main/BUILD>
- <https://stackoverflow.com/questions/72488330/mediapipe-how-to-configure-debugger-using-vs-code-and-bazel>