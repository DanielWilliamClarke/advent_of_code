const std = @import("std");
const io = @import("./io.zig");
const out = @import("./out.zig");
const time = @import("./time.zig");

pub fn runParts(
    alloc: std.mem.Allocator,
    input_path: []const u8,
    comptime part1: fn ([][]u8) i64,
    comptime part2: fn ([][]u8) i64,
) !void {
    const lines = try io.readLinesOwned(alloc, input_path);
    defer {
        for (lines) |line| alloc.free(line);
        alloc.free(lines);
    }

    var t1 = try time.startTimer();
    const res1 = part1(lines);
    const ns1 = time.readNs(&t1);

    var t2 = try time.startTimer();
    const res2 = part2(lines);
    const ns2 = time.readNs(&t2);

    out.printPart(1, res1);
    out.printTimed("part1", ns1);
    out.printPart(2, res2);
    out.printTimed("part2", ns2);
}
