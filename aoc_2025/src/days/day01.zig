const std = @import("std");
const io = @import("../util/io.zig");
const out = @import("../util/out.zig");
const time = @import("../util/time.zig");

const std = @import("std");
const runner = @import("../util/runner.zig");

fn part1(lines: [][]const u8) !i64 {
    var sum: i64 = 0;
    for (lines) |line| {
        if (line.len == 0) continue;
        sum += try std.fmt.parseInt(i64, line, 10);
    }
    return sum;
}

fn part2(lines: [][]const u8) !i64 {
    var sum: i64 = 0;
    for (lines) |line| {
        if (line.len == 0) continue;
        const v = try std.fmt.parseInt(i64, line, 10);
        sum += v * 2; // pretend Part 2 rule
    }
    return sum;
}

pub fn run(alloc: std.mem.Allocator, input_path: []const u8) !void {
    try runner.runParts(alloc, input_path, part1, part2);
}

// Optional: unit tests for day logic
test "day01 example" {
    const alloc = std.testing.allocator;
    const data = "1\n2\n3\n";

    // Write to a tmp file to test read+solve end-to-end.
    var tmp = std.testing.tmpDir(.{});
    defer tmp.cleanup();
    try tmp.dir.writeFile("input.txt", data);

    try run(alloc, "input.txt");
}
