const std = @import("std");
const out = @import("util/out.zig");
const day = @import("util/day.zig");

// Days dispatcher: add new days to the switch as you implement them
const Days = struct {
    fn makeDay(comptime Mod: type) day.Day {
        return .{
            .example_path = Mod.example_path,
            .input_path = Mod.input_path,
            .part1 = Mod.part1,
            .part2 = Mod.part2,
        };
    }

    fn get(day_num: u8) !day.Day {
        return switch (day_num) {
            0 => makeDay(@import("days/day00.zig")),
            1 => makeDay(@import("days/day01.zig")),
            // 2 => @import("days/day02.zig").spec,
            else => error.UnknownDay,
        };
    }

    pub fn run(day_num: u8, alloc: std.mem.Allocator) !void {
        try (try get(day_num)).run(alloc);
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
