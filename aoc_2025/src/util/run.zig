const std = @import("std");
const io = @import("./io.zig");
const out = @import("./out.zig");
const time = @import("./time.zig");

// Framework for running both parts of a day's puzzle with timing
// Reads input file, runs part1 and part2, prints results with timing info
pub fn runParts(
    alloc: std.mem.Allocator,
    input_path: []const u8,
    part1: *const fn ([]const []const u8) anyerror!i64, // Part functions can return errors
    part2: *const fn ([]const []const u8) anyerror!i64,
) !void {
    // Read input file into lines (caller must provide allocator)
    const lines = try io.readLinesOwned(alloc, input_path);
    defer {
        for (lines) |line| alloc.free(line); // Free each line
        alloc.free(lines); // Free the slice itself
    }

    // Time and run part 1
    var t1 = try time.startTimer();
    const res1 = try part1(lines); // try propagates errors up
    const ns1 = time.readNs(&t1);

    // Time and run part 2
    var t2 = try time.startTimer();
    const res2 = try part2(lines);
    const ns2 = time.readNs(&t2);

    // Print results and timing
    out.printPart(1, res1);
    out.printTimed("part1", ns1);
    out.printPart(2, res2);
    out.printTimed("part2", ns2);
}
