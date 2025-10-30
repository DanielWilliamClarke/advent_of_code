const std = @import("std");
const tree = @import("./tree.zig");

pub fn printHeader(day: u8) void {
    tree.printTree(day);
}

pub fn printPart(part: u8, value: anytype) void {
    std.debug.print("Gift {d}: {}\n", .{ part, value });
}

pub fn printTimed(label: []const u8, ns: u64) void {
    // Pretty print with automatic unit scaling
    if (ns < 1_000) {
        std.debug.print("{s} wrapped in {d} ns\n", .{ label, ns });
    } else if (ns < 1_000_000) {
        std.debug.print("{s} wrapped in {d} us\n", .{ label, ns / 1_000 });
    } else if (ns < 1_000_000_000) {
        std.debug.print("{s} wrapped in {d} ms\n", .{ label, ns / 1_000_000 });
    } else {
        std.debug.print("{s} wrapped in {d} s\n", .{ label, ns / 1_000_000_000 });
    }
}
