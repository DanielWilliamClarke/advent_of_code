const std = @import("std");
const io = @import("./io.zig");

pub fn validate(
    partFn: *const fn (std.mem.Allocator, []const []const u8) anyerror!i64,
) ValidateBuilder {
    return .{ .partFn = partFn };
}

const ValidateBuilder = struct {
    partFn: *const fn (std.mem.Allocator, []const []const u8) anyerror!i64,
    input_path: ?[]const u8 = null,

    pub fn with(self: ValidateBuilder, input_path: []const u8) ValidateBuilder {
        return .{
            .partFn = self.partFn,
            .input_path = input_path,
        };
    }

    pub fn equals(self: ValidateBuilder, expected: i64) !void {
        const alloc = std.testing.allocator;

        const input_path = self.input_path orelse @panic("input_path not set");
        const lines = try io.readLinesOwned(alloc, input_path);
        defer io.freeLinesOwned(alloc, lines);

        const result = try self.partFn(alloc, lines);
        try std.testing.expectEqual(expected, result);
    }
};
