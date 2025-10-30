const std = @import("std");
const out = @import("util/out.zig");

// Days dispatcher: add new days to the switch as you implement them
const Days = struct {
    pub fn run(day: u8, alloc: std.mem.Allocator) !void {
        switch (day) {
            0 => return @import("days/day00.zig").Day.run(alloc),
            1 => return @import("days/day01.zig").Day.run(alloc),
            // 2 => return @import("days/day02.zig").Day.run(alloc),
            // ... add more days as you complete them
            else => return error.UnknownDay,
        }
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
    const day = try std.fmt.parseInt(u8, day_str, 10);

    out.printHeader(day);

    if (Days.run(day, alloc)) |_| {
        // success
    } else |err| switch (err) {
        error.FileNotFound => std.debug.print("Input not found for day {d}\n", .{day}),
        error.UnknownDay => std.debug.print("Unknown day: {d}\n", .{day}),
        else => return err,
    }
}
