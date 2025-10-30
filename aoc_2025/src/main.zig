const std = @import("std");
const out = @import("util/out.zig");

// Days dispatcher: add new days to the switch as you implement them
const Days = struct {
    pub fn run(day: u8, alloc: std.mem.Allocator, input_path: []const u8) !void {
        switch (day) {
            1 => return @import("days/day01.zig").run(alloc, input_path),
            // 2 => return @import("days/day02.zig").run(alloc, input_path),
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
        std.debug.print("usage: aoc <day> [input_path]\n", .{});
        return;
    };
    const day = try std.fmt.parseInt(u8, day_str, 10);

    // Use custom input path, or default to inputs/dayXX.txt
    const input_path = args.next() orelse blk: {
        var buf: [64]u8 = undefined;
        const path = try std.fmt.bufPrint(&buf, "inputs/day{0d:0>2}.txt", .{day});
        break :blk try alloc.dupe(u8, path);
    };
    defer alloc.free(input_path);

    out.printHeader(day);

    if (Days.run(day, alloc, input_path)) |_| {
        // success
    } else |err| switch (err) {
        error.FileNotFound => std.debug.print("Input not found: {s}\n", .{input_path}),
        error.UnknownDay => std.debug.print("Unknown day: {d}\n", .{day}),
        else => return err,
    }
}
