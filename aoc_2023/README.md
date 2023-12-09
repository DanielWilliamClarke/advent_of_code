# AdventOfCode2023 🎄

This year I will be dusting off my C++ skills and learning more about Modern C++.

I will be targetting `C++20` and compiling using Bazel.

I am also taking this time to trial out CLion from Intellij.

## Install dependencies

### MacOS

- [ ] Install XCode from the Appstore

```bash
# for the first time you will need agree to the XCode license
sudo xcode-select --install 
sudo xcode-select --switch /Applications/Xcode.app # this was a bit of a faff
sudo xcodebuild -license accept

brew install bazel

brew install scarvalhojr/tap/aoc-cli
# Add session to aoc-cli following instructions from https://github.com/scarvalhojr/aoc-cli
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

## Create AOC days and fetch input from aoc-cli

```bash
chmod +x ./new_day

./new_day <DAY>

# ✨  Creating day 10 directory: main/days/10 
# ✨  Creating day 10 header file: [main/days/10/day_10.h] 
# ✨  Creating day 10 source file: [main/days/10/day_10.cpp] 
# ✨  Creating day 10 test file: [test/days/10/day10.cpp] 
# 🔨  Adding day 10 to main.cpp 
# 📬  Downloading AOC day 10 data 
# [INFO  aoc] 🎄 aoc-cli - Advent of Code command-line tool
# [INFO  aoc_client] 🎅 Saved puzzle to 'main/days/10/puzzle.md'
# [INFO  aoc_client] 🎅 Saved input to 'main/days/10/input.txt'
```

#### Project Dependencies

This project makes use of:

- `range-v3`: <https://ericniebler.github.io/range-v3/> 
- `gtest`: <https://github.com/google/googletest>

#### Implementation Note

The project is favoring inheritance over composition to emulate Rust traits and to reduce the amount of boilerplate code required to construct each Day's solution 

## Visualise class diagram

```bash
brew install graphviz xdot 
 
xdot <(bazel query --notool_deps --noimplicit_deps "deps(//test:aoc-2023)" --output graph)
```

## Resources

- <https://bazel.build/start/cpp>
- <https://bazel.build/tutorials/cpp-use-cases>
- <https://google.github.io/googletest/quickstart-bazel.html>
- <https://apple.stackexchange.com/questions/175069/how-to-accept-xcode-license>
- <https://marketplace.visualstudio.com/items?itemName=BazelBuild.vscode-bazel>
- <https://github.com/bazelbuild/examples/blob/main/cpp-tutorial/stage3/main/BUILD>
- <https://stackoverflow.com/questions/72488330/mediapipe-how-to-configure-debugger-using-vs-code-and-bazel>
- <https://youtu.be/-TUogVOs1Qg?feature=shared>
- <https://ericniebler.github.io/range-v3/>
- <https://github.com/scarvalhojr/aoc-cli>