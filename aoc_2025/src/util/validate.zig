const std = @import("std");
const io = @import("./io.zig");

// Helper for testing day solutions against expected results from a specific input file
// Usage: try validate("inputs/day01.txt", part1, 12345);
pub fn validate(
    input_path: []const u8,
    comptime partFn: fn ([][]const u8) anyerror!i64,
    expected: i64,
) !void {
    const alloc = std.testing.allocator;

    const lines = try io.readLinesOwned(alloc, input_path);
    defer {
        for (lines) |line| alloc.free(line);
        alloc.free(lines);
    }

    const result = try partFn(lines);
    try std.testing.expectEqual(expected, result);
}
