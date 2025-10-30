const std = @import("std");

pub fn printHeader(day: u8) void {
    std.debug.print("\n== Day {d} ==\n", .{day});
}

pub fn printPart(part: u8, value: anytype) void {
    std.debug.print("Part {d}: {}\n", .{ part, value });
}

pub fn printTimed(label: []const u8, ns: u64) void {
    // Pretty print with automatic unit scaling
    if (ns < 1_000) {
        std.debug.print("{s}: {d} ns\n", .{ label, ns });
    } else if (ns < 1_000_000) {
        std.debug.print("{s}: {d} us\n", .{ label, ns / 1_000 });
    } else if (ns < 1_000_000_000) {
        std.debug.print("{s}: {d} ms\n", .{ label, ns / 1_000_000 });
    } else {
        std.debug.print("{s}: {d} s\n", .{ label, ns / 1_000_000_000 });
    }
}
