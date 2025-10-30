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
│       ├── run.zig        # Framework for running parts
│       ├── time.zig       # Timing/benchmarking
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
const day = @import("../util/day.zig");

pub const dayXX = day.fromImpl(struct {
    pub const input_path = "inputs/dayXX.txt";
    pub const example_path = "inputs/dayXX_example.txt";

    pub fn part1(lines: []const []const u8) !i64 {
        // Your solution here
        return 0;
    }

    pub fn part2(lines: []const []const u8) !i64 {
        // Your solution here
        return 0;
    }
});

// ========== Tests ==========

test "dayXX example" {
    try validate.validate(dayXX.example_path, dayXX.part1, 42); // Replace with example answer
}

test "dayXX part1" {
    try validate.validate(dayXX.input_path, dayXX.part1, 12345); // Replace with actual answer
}

test "dayXX part2" {
    try validate.validate(dayXX.input_path, dayXX.part2, 67890); // Replace with actual answer
}
```

Key points:
   - Export a constant named `dayXX` created via `day.fromImpl()`
   - Pass an anonymous struct with `input_path`, `example_path`, `part1`, and `part2`
   - The compiler will verify your struct matches the Day interface at compile time
   - Use the exported constant in tests (e.g., `dayXX.part1`, `dayXX.example_path`)

2. Add the day to `src/main.zig` (in the Days.get() switch):
```zig
const Days = struct {
    pub fn get(day_num: u8) !day.Day {
        return switch (day_num) {
            0 => @import("days/day00.zig").day00,
            XX => @import("days/dayXX.zig").dayXX,  // Add this line
            else => error.UnknownDay,
        };
    }
    // ...
};
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

### Duck-Typed Day Interface

This project uses Zig's compile-time type system to achieve a duck-typed interface pattern for daily solutions. Here's how it works:

#### The Day Struct (`util/day.zig`)
```zig
pub const Day = struct {
    example_path: []const u8,
    input_path: []const u8,
    part1: *const fn ([]const []const u8) anyerror!i64,
    part2: *const fn ([]const []const u8) anyerror!i64,
};
```

The `Day` struct acts as a **runtime interface** containing:
- File paths for input and example data
- Function pointers to `part1` and `part2` implementations

#### The fromImpl Function
```zig
pub fn fromImpl(comptime Impl: type) Day {
    return .{
        .example_path = Impl.example_path,
        .input_path = Impl.input_path,
        .part1 = Impl.part1,
        .part2 = Impl.part2,
    };
}
```

This function performs **compile-time duck typing**:
- Takes any type (`comptime Impl: type`) as a parameter
- At compile time, Zig checks that the type has the required fields/functions
- If valid, extracts the fields and creates function pointers
- Returns a concrete `Day` instance

#### Day Implementation Pattern (`days/dayXX.zig`)
```zig
pub const dayXX = day.fromImpl(struct {
    pub const input_path = "inputs/dayXX.txt";
    pub const example_path = "inputs/dayXX_example.txt";

    pub fn part1(lines: []const []const u8) !i64 {
        // Solution here
    }

    pub fn part2(lines: []const []const u8) !i64 {
        // Solution here
    }
});
```

Each day exports a **constant** (e.g., `day00`, `day01`) created by:
1. Defining an anonymous struct with the required shape
2. Passing it to `day.fromImpl()` at compile time
3. The compiler verifies the struct has the right structure
4. A `Day` instance is created with function pointers to the implementations

#### The Dispatcher (`main.zig`)
```zig
const Days = struct {
    pub fn get(day_num: u8) !day.Day {
        return switch (day_num) {
            0 => @import("days/day00.zig").day00,
            1 => @import("days/day01.zig").day01,
            else => error.UnknownDay,
        };
    }
};
```

The dispatcher returns the appropriate `Day` struct based on user input, which is then passed to the runner framework.

#### Why This Pattern?

This achieves **interface-like polymorphism** without runtime overhead:
- **Compile-time safety**: The compiler enforces that each day has the correct structure
- **No vtables**: Function pointers are created once at compile time
- **Duck typing**: Any type that "looks like" a Day can be converted to one
- **Zero cost abstraction**: No runtime penalty compared to calling functions directly

### Memory Management
- Zig uses manual memory management via **allocators**
- `GeneralPurposeAllocator` in main.zig tracks memory leaks
- Always `defer` cleanup (e.g., `defer alloc.free(memory)`)

### Error Handling
- `!` prefix means a function can return an error (e.g., `!i64`)
- `try` keyword propagates errors up the call stack
- Functions can fail and must handle or propagate errors

### Framework Flow
1. `main.zig` parses CLI args and calls `Days.get(day_num)` to retrieve the `Day` struct
2. The `Day` struct (containing function pointers) is passed to `runner.runParts()`
3. `runner.runParts()` reads input, times both parts, and prints results
4. Utility modules (`io`, `out`, `time`) handle file I/O, formatting, and timing

### Key Zig Concepts
- **comptime**: Compile-time evaluation - used here for duck typing via `fromImpl`
- **Allocator**: Memory manager passed explicitly (not global)
- **Slices**: `[]T` is a pointer + length (not null-terminated)
- **const**: Immutable data (e.g., `[]const u8` is a read-only string)
- **defer**: Runs code when scope exits (like Go's defer or C++'s RAII)
- **try**: Shorthand for error propagation (returns early if error)
- **Function pointers**: `*const fn(Args) Return` - used to store day implementations

## Tips

- Use `std.debug.print()` for debugging (prints to stderr)
- Input files are not committed to git (see `.gitignore`)
- The framework automatically times your solutions
- Write tests in your day files using `test "name" { ... }`
