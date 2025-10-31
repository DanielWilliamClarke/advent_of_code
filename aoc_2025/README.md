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

1. Create `src/days/dayXX.zig`:

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

2. Add the day to `src/main.zig` (in the Days.get switch):

```zig
XX => makeDay(@import("days/dayXX.zig")),
```

3. Add the day to `src/test.zig`:

```zig
test {
    _ = @import("days/day00.zig");
    _ = @import("days/day01.zig");
    _ = @import("days/dayXX.zig");  // Add this line
}
```

4. Add input files:

   - `inputs/dayXX_example.txt` - Example input from the puzzle description
   - `inputs/dayXX.txt` - Your actual puzzle input

5. Run the example test to verify your solution logic works with the example
6. Run your solution to get the actual answers
7. Update test expectations with correct answers and run `zig build test` to validate

## How It Works

### Day Descriptor (`util/day.zig`)

```zig
pub const Day = struct {
    example_path: []const u8,
    input_path: []const u8,
    part1: *const fn (std.mem.Allocator, []const []const u8) anyerror!i64,
    part2: *const fn (std.mem.Allocator, []const []const u8) anyerror!i64,

    pub fn run(self: Day, alloc: std.mem.Allocator) !void {
        const lines = try io.readLinesOwned(alloc, self.input_path);
        defer {
            for (lines) |line| alloc.free(line);
            alloc.free(lines);
        }

        var t1 = try time.startTimer();
        const res1 = try self.part1(alloc, lines);
        const ns1 = time.readNs(&t1);

        var t2 = try time.startTimer();
        const res2 = try self.part2(alloc, lines);
        const ns2 = time.readNs(&t2);

        out.printPart(1, res1);
        out.printTimed("part1", ns1);
        out.printPart(2, res2);
        out.printTimed("part2", ns2);
    }
};
```

`Day` is a lightweight runtime descriptor. Each instance stores the file paths plus function pointers for `part1` and `part2`, while `run` centralises input loading, timing, and printing.

### Day Modules (`src/days/dayXX.zig`)

Each day module exports just the data and functions that back the descriptor:

```zig
pub const input_path = "inputs/dayXX.txt";
pub const example_path = "inputs/dayXX_example.txt";

pub fn part1(_: std.mem.Allocator, lines: []const []const u8) !i64 {
    // Solution here
}

pub fn part2(_: std.mem.Allocator, lines: []const []const u8) !i64 {
    // Solution here
}
```

Tests in the file call `validate.validate`, which expects the allocator-aware function signature shown above.

### Dispatcher (`src/main.zig`)

```zig
const Days = struct {
    fn makeDay(comptime Mod: type) day.Day {
        return .{
            .example_path = Mod.example_path,
            .input_path = Mod.input_path,
            .part1 = Mod.part1,
            .part2 = Mod.part2,
        };
    }

    fn get(day_num: u8) !day.Day {
        return switch (day_num) {
            0 => makeDay(@import("days/day00.zig")),
            1 => makeDay(@import("days/day01.zig")),
            else => error.UnknownDay,
        };
    }

    pub fn run(day_num: u8, alloc: std.mem.Allocator) !void {
        try (try get(day_num)).run(alloc);
    }
};
```

`main` parses CLI arguments, prints a header, and delegates to `Days.run`. The selected module is wrapped on demand, so adding a new day only requires an extra `makeDay(@import(...))` branch.

### Execution Flow

1. Parse the requested day number from the CLI.
2. Import that day module and wrap it in a `day.Day` descriptor.
3. `Day.run` reads the puzzle input, runs both parts with the shared allocator, and records timings.
4. Results and timings are printed via the shared `out` helpers.

### Why This Pattern

- `Day` is the runtime bundle for a puzzle: it keeps the file paths plus callable pointers to `part1`/`part2`, and its `run` method centralises I/O, memory management, and timing so every day inherits the same harness.
- `Days` is the compile-time dispatcher: `makeDay` converts whatever the module exports into a `Day`, `get` selects the right module for the CLI argument, and `run` hands execution over to the shared harness.
- This lets each day module focus solely on puzzle logic (`input_path`, `example_path`, `part1`, `part2`) while the framework guarantees consistent orchestration and reporting.
- The split keeps infrastructure changes confined to `util/day.zig` and `main.zig`, so adding instrumentation or new features does not touch puzzle code.

### Key Zig Concepts

- **Allocator**: Every allocation is explicit; the same allocator is passed into each part.
- **Slices**: `[]T` represents a pointer + length, used for the input lines.
- **Function pointers**: `*const fn (Allocator, [][]const u8) anyerror!T` lets us store callbacks inside `Day`.
- **defer**: Guarantees that allocated buffers are freed even when errors occur.
- **try**: Propagates errors without boilerplate handling code.
- **comptime imports**: `@import` inside the switch runs at compile time, so unused days do not incur runtime cost.

## Tips

- Use `std.debug.print()` for debugging (prints to stderr).
- Input files are not committed to git (see `.gitignore`).
- The framework automatically times your solutions.
- Write tests in your day files using `test "name" { ... }`.
