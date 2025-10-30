pub const Day = struct {
    input_path: []const u8,
    part1: *const fn ([]const []const u8) anyerror!i64,
    part2: *const fn ([]const []const u8) anyerror!i64,
};
