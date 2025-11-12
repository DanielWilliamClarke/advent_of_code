const std = @import("std");

const day = @import("./day.zig");

// Days dispatcher: add new days to the switch as you implement them
pub const Runner = struct {
    fn getImpl(num: i32) !day.Day {
        return switch (num) {
            20201 => day.Day.fromImpl(@import("../days/day01x2020.zig")),
            20202 => day.Day.fromImpl(@import("../days/day02x2020.zig")),
            1 => day.Day.fromImpl(@import("../days/day01.zig")),
            // 2 => @import("days/day02.zig").spec,
            else => error.UnknownDay,
        };
    }

    pub fn run(alloc: std.mem.Allocator, num: i32) void {
        const impl = getImpl(num) catch |err| {
            std.log.err("Unknown day: {d} - {}", .{ num, err });
            return;
        };
        impl.run(alloc) catch |err| {
            switch (err) {
                error.FileNotFound => std.log.err("Input not found for day {d} - {}", .{ num, err }),
                else => std.log.err("run failed for day {d}: {}", .{ num, err }),
            }
            return;
        };
    }
};
