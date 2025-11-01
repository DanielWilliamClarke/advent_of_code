const std = @import("std");
const tree = @import("./tree.zig");

pub fn printHeader(day: u8) void {
    tree.printTree(day);
}

pub fn printPart(part: u8, value: anytype) void {
    std.debug.print("Gift {d}: {}\n", .{ part, value });
}

pub const Unit = enum {
    auto,
    nanos,
    micros,
    millis,
    seconds,
};

pub fn printTimed(label: []const u8, ns: u64, unit: Unit) void {
    switch (unit) {
        .nanos => {
            std.debug.print("{s} took {d} nanoseconds\n", .{ label, ns });
        },
        .micros => {
            std.debug.print("{s} took {d:.2} microseconds\n", .{ label, @as(f64, @floatFromInt(ns)) / 1e3 });
        },
        .millis => {
            std.debug.print("{s} took {d:.2} milliseconds\n", .{ label, @as(f64, @floatFromInt(ns)) / 1e6 });
        },
        .seconds => {
            std.debug.print("{s} took {d:.2} seconds\n", .{ label, @as(f64, @floatFromInt(ns)) / 1e9 });
        },
        .auto => {
            if (ns < 1_000) {
                std.debug.print("{s} took {d} nanoseconds\n", .{ label, ns });
            } else if (ns < 1_000_000) {
                std.debug.print("{s} took {d:.2} microseconds\n", .{ label, @as(f64, @floatFromInt(ns)) / 1e3 });
            } else if (ns < 1_000_000_000) {
                std.debug.print("{s} took {d:.2} milliseconds\n", .{ label, @as(f64, @floatFromInt(ns)) / 1e6 });
            } else {
                std.debug.print("{s} took {d:.2} seconds\n", .{ label, @as(f64, @floatFromInt(ns)) / 1e9 });
            }
        },
    }
}
