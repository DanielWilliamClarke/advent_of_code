const std = @import("std");
const out = @import("util/out.zig");
const aoc = @import("util/runner.zig");

pub fn main() !void {
    // Memory allocator with leak detection
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const alloc = gpa.allocator();

    // Parse command-line arguments
    var args = try std.process.argsWithAllocator(alloc);
    defer args.deinit();

    // skipexecutable name
    _ = args.next();

    // Get day number
    const day_str = args.next() orelse {
        std.debug.print("usage: aoc <day>\n", .{});
        return;
    };

    const day_num = try std.fmt.parseInt(u8, day_str, 10);
    out.printHeader(day_num);
    aoc.Runner.run(alloc, day_num);
}
