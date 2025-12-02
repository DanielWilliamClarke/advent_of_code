// Test entry point - imports all day modules for testing
// Add new days here as you implement them

test {
    // infra tests
    _ = @import("util/parser.zig");

    // practice tests
    _ = @import("practice/day01x2020.zig");
    _ = @import("practice/day02x2020.zig");
    _ = @import("practice/day03x2020.zig");

    // 2024 tests
    // _ = @import("days/day00.zig");
    _ = @import("days/day01.zig");
    _ = @import("days/day02.zig");
    // _ = @import("days/day03.zig");
    // ...
}
