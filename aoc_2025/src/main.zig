const std = @import("std");
const out = @import("util/out.zig");
const runner = @import("util/run.zig");
const day = @import("util/day.zig");

// Days dispatcher: add new days to the switch as you implement them
const Days = struct {
    pub fn get(day_num: u8) !day.Day {
        return switch (day_num) {
            0 => @import("days/day00.zig").day00,
            1 => @import("days/day01.zig").day01,
            // 2 => @import("days/day02.zig").spec,
            else => error.UnknownDay,
        };
    }

    pub fn run(day_num: u8, alloc: std.mem.Allocator) !void {
        const d = try get(day_num); // <-- returns the day struct or error
        try runner.runParts(alloc, d.input_path, d.part1, d.part2);
    }
};

pub fn main() !void {
    // Memory allocator with leak detection
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const alloc = gpa.allocator();

    // Parse command-line arguments
    var args = try std.process.argsWithAllocator(alloc);
    defer args.deinit();

    _ = args.next(); // executable name

    const day_str = args.next() orelse {
        std.debug.print("usage: aoc <day>\n", .{});
        return;
    };
    const day_num = try std.fmt.parseInt(u8, day_str, 10);

    out.printHeader(day_num);

    if (Days.run(day_num, alloc)) |_| {
        // success
    } else |err| switch (err) {
        error.FileNotFound => std.debug.print("Input not found for day {d}\n", .{day_num}),
        error.UnknownDay => std.debug.print("Unknown day: {d}\n", .{day_num}),
        else => return err,
    }
}
