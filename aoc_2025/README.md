# Advent of Code 2025

Zig solutions for Advent of Code 2025.

## Prerequisites

- Zig 0.15.1 or newer

## Project Structure

```
aoc_2025/
├── build.zig              # Build configuration
├── src/
│   ├── main.zig           # Entry point with day dispatcher
│   ├── test.zig           # Test entry point (imports all day tests)
│   ├── days/
│   │   ├── day00.zig      # Day 0 warm-up / template
│   │   └── day01.zig      # Day 1 solution (add more as you go)
│   └── util/
│       ├── io.zig         # File reading utilities
│       ├── out.zig        # Output formatting
│       ├── time.zig       # Timing/benchmarking
│       ├── day.zig        # Day descriptor + runner
│       ├── tree.zig       # ASCII tree banner for output
│       └── validate.zig   # Test validation helper
└── inputs/
    ├── day00.txt          # Day 0 puzzle input
    ├── day00_example.txt  # Day 0 example input
    ├── day01.txt          # Day 1 puzzle input
    └── day01_example.txt  # Day 1 example input
```

## Usage

### Build the project

```bash
zig build
```

### Run a specific day

```bash
zig build run -- <day_number>
```

Examples:

```bash
zig build run -- 0          # Runs day 0 with inputs/day00.txt
zig build run -- 1          # Runs day 1 with inputs/day01.txt
```

### Run without building first

```bash
zig run src/main.zig -- <day_number>
```

### Run tests

```bash
zig build test                             # Run all tests (summary)
zig build test --summary all               # Show build summary
zig test src/test.zig                      # Direct test (summary)
zig test src/test.zig --test-filter ""     # All tests with verbose output
zig test src/test.zig --test-filter "day01"  # Run only day01 tests
```

## Adding a New Day

1. Create `src/days/dayXX.zig` using the template below, then fill in the solver logic and expected answers in the tests.

```zig
const std = @import("std");
const validate = @import("../util/validate.zig");

pub const input_path = "inputs/dayXX.txt";
pub const example_path = "inputs/dayXX_example.txt";

pub fn part1(_: std.mem.Allocator, lines: []const []const u8) !i64 {
    // Your solution here
    return 0;
}

pub fn part2(_: std.mem.Allocator, lines: []const []const u8) !i64 {
    // Your solution here
    return 0;
}

// ========== Tests ==========

test "dayXX example" {
    try validate.validate(example_path, part1, 42); // Replace with example answer
}

test "dayXX part1" {
    try validate.validate(input_path, part1, 12345); // Replace with actual answer
}

test "dayXX part2" {
    try validate.validate(input_path, part2, 67890); // Replace with actual answer
}
```

2. Copy the template or reuse `src/days/day00.zig` as a starting point, adjusting the constants, solver functions, and test expectations for day XX.
3. Register the module in `src/util/runner.zig` by adding a branch inside `Runner.getImpl` that returns `day.Day.fromImpl(@import("../days/dayXX.zig"))`.
4. Import the module in `src/test.zig` so the aggregated test harness picks up the new day.
5. Add input files:
   - `inputs/dayXX_example.txt` - Example input from the puzzle description
   - `inputs/dayXX.txt` - Your actual puzzle input
6. Run the example test to verify your solution logic works with the example.
7. Run your solution to get the actual answers.
8. Update test expectations with correct answers and run `zig build test` to validate.

## How It Works

### Day Descriptor (`src/util/day.zig`)

`Day` is a lightweight runtime descriptor. The struct stores the example and input file paths plus function pointers for `part1` and `part2`, while `run` centralises input loading, timing, and printing. The `fromImpl` helper bundles a day module into the struct in one call.

### Day Modules (`src/days/dayXX.zig`)

Each day module declares `input_path`, `example_path`, and the two solver functions. Inline tests call `validate.validate` so the same allocator-aware signature is reused. Refer to `src/days/day00.zig` and `src/days/day01.zig` for concrete patterns.

### Dispatcher (`src/util/runner.zig`)

`Runner.getImpl` imports the requested module at comptime and wraps it with `day.Day.fromImpl`, while `Runner.run` executes the bundled struct and logs any errors. This centralises the list of implemented days and keeps puzzle files free of runner concerns.

`src/main.zig` parses CLI arguments, prints the header via `util/out.zig`, then invokes `Runner.run`. Adding a new day only requires updating the switch in `getImpl` and importing the module in `src/test.zig`.

### Execution Flow

1. Parse the requested day number from the CLI.
2. Import that day module and wrap it in a `day.Day` descriptor.
3. `Day.run` reads the puzzle input, runs both parts with the shared allocator, and records timings.
4. Results and timings are printed via the shared `out` helpers.

### Why This Pattern

- `Day` is the runtime bundle for a puzzle: it keeps the file paths plus callable pointers to `part1`/`part2`, and its `run` method centralises I/O, memory management, and timing so every day inherits the same harness.
- `Runner` is the compile-time dispatcher: `getImpl` selects the right module for the CLI argument, and `run` hands execution over to the shared harness.
- This lets each day module focus solely on puzzle logic (`input_path`, `example_path`, `part1`, `part2`) while the framework guarantees consistent orchestration and reporting.
- The split keeps infrastructure changes confined to `util/day.zig`, `util/runner.zig`, and `main.zig`, so adding instrumentation or new features does not touch puzzle code.

### Key Zig Concepts

- **Allocator**: Every allocation is explicit; the same allocator is passed into each part.
- **Slices**: `[]T` represents a pointer + length, used for the input lines.
- **Function pointers**: `*const fn (Allocator, [][]const u8) anyerror!T` lets us store callbacks inside `Day`.
- **defer**: Guarantees that allocated buffers are freed even when errors occur.
- **try**: Propagates errors without boilerplate handling code.
- **comptime imports**: `@import` inside the switch runs at compile time, so unused days do not incur runtime cost.

## Parsing Inputs

We lean on the [`mecha`](https://github.com/Hejsil/mecha) parser combinator library to turn raw puzzle input into typed structures. Favor building reusable mecha parsers over ad-hoc regular expressions so input handling stays idiomatic Zig and easier to maintain.

## Tips

- Use `std.debug.print()` for debugging (prints to stderr).
- Input files are not committed to git (see `.gitignore`).
- The framework automatically times your solutions.
- Write tests in your day files using `test "name" { ... }`.

## Debugging `aoc_2025` with LLDB

Since debugger support for Zig appears to be quite limited, lets trial using LLDB

1. Build the project in debug mode (the default) so LLDB can inspect symbols: `cd aoc_2025 && zig build`.
2. Launch LLDB against the freshly built binary: `lldb aoc_2025/zig-out/bin/aoc_2025`.
3. Set any breakpoints you need, for example `b main; b ./day/day00.zig:23` or target a specific day handler such as `Day.run`.
   3.i. List breakpoints with br list, delete breakpoints with br delete <number>
   3.ii. useful commands, `step`, `continue`, `down`, `frame variable`
4. Run the executable with Advent of Code arguments via LLDB, e.g. `run 1` to debug day 1.

A concise walkthrough of these LLDB basics is in [this debugging video](https://www.youtube.com/watch?v=FDfFUJM1UOw&t=255s), which pairs nicely with the steps above.
