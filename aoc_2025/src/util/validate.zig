const std = @import("std");
const io = @import("./io.zig");

// Internal helper to run validation with a given input path
fn validateWithPath(
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

// Helper for testing day solutions against expected results from actual input file
// Usage: try validate(1, part1, 12345);
pub fn validate(
    day: u8,
    comptime partFn: fn ([][]const u8) anyerror!i64,
    expected: i64,
) !void {
    var buf: [64]u8 = undefined;
    const input_path = try std.fmt.bufPrint(&buf, "inputs/day{0d:0>2}.txt", .{day});
    try validateWithPath(input_path, partFn, expected);
}

// Helper for testing with example input from inputs/dayXX_example.txt
// Usage: try validateExample(1, part1, 42);
pub fn validateExample(
    day: u8,
    comptime partFn: fn ([][]const u8) anyerror!i64,
    expected: i64,
) !void {
    var buf: [64]u8 = undefined;
    const input_path = try std.fmt.bufPrint(&buf, "inputs/day{0d:0>2}_example.txt", .{day});
    try validateWithPath(input_path, partFn, expected);
}