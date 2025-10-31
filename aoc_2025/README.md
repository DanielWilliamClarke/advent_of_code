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
│   │   ├── day01.zig      # Day 1 solution
│   │   └── day02.zig      # Day 2 solution (add as you go)
│   └── util/
│       ├── io.zig         # File reading utilities
│       ├── out.zig        # Output formatting
│       ├── time.zig       # Timing/benchmarking
│       ├── day.zig        # Day descriptor + runner
│       └── validate.zig   # Test validation helper
└── inputs/
    ├── day01.txt          # Day 1 puzzle input
    ├── day01_example.txt  # Day 1 example input
    └── day02.txt          # Day 2 puzzle input (add as you go)
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
zig build run -- 1          # Runs day 1 with inputs/day01.txt
zig build run -- 2          # Runs day 2 with inputs/day02.txt
```

### Use a custom input file
```bash
zig build run -- 1 path/to/custom_input.txt
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

### Memory Management
- Zig uses manual memory management via **allocators**
- `GeneralPurposeAllocator` in main.zig tracks memory leaks
- Always `defer` cleanup (e.g., `defer alloc.free(memory)`)

### Error Handling
- `!` prefix means a function can return an error (e.g., `!i64`)
- `try` keyword propagates errors up the call stack
- Functions can fail and must handle or propagate errors

### Framework Flow
1. `main.zig` parses CLI args and loads the day's `day.Day` descriptor
2. `Day.run()` reads the input, times both parts, and prints results
3. Utility modules (`io`, `out`, `time`) handle file I/O, formatting, and timing

### Key Zig Concepts
- **Allocator**: Memory manager passed explicitly (not global)
- **Slices**: `[]T` is a pointer + length (not null-terminated)
- **const**: Immutable data (e.g., `[]const u8` is a read-only string)
- **defer**: Runs code when scope exits (like Go's defer or C++'s RAII)
- **try**: Shorthand for error propagation (returns early if error)
- **comptime**: Compile-time evaluation (used for generic programming)

## Tips

- Use `std.debug.print()` for debugging (prints to stderr)
- Input files are not committed to git (see `.gitignore`)
- The framework automatically times your solutions
- Write tests in your day files using `test "name" { ... }`
