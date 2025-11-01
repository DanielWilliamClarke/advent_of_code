const std = @import("std");
const io = @import("./io.zig");
const out = @import("./out.zig");
const time = @import("./time.zig");

pub const Day = struct {
    input_path: []const u8,
    part1: *const fn (std.mem.Allocator, []const []const u8) anyerror!i64,
    part2: *const fn (std.mem.Allocator, []const []const u8) anyerror!i64,

    pub fn fromImpl(comptime Mod: type) Day {
        return .{
            .input_path = Mod.input_path,
            .part1 = Mod.part1,
            .part2 = Mod.part2,
        };
    }

    pub fn run(self: Day, alloc: std.mem.Allocator) !void {
        const lines = try io.readLinesOwned(alloc, self.input_path);
        defer io.freeLinesOwned(alloc, lines);

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
