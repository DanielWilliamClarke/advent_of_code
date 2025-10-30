pub const Day = struct {
    example_path: []const u8,
    input_path: []const u8,
    part1: *const fn ([]const []const u8) anyerror!i64,
    part2: *const fn ([]const []const u8) anyerror!i64,
};

pub fn fromImpl(comptime Impl: type) Day {
    return .{
        .example_path = Impl.example_path,
        .input_path = Impl.input_path,
        .part1 = Impl.part1,
        .part2 = Impl.part2,
    };
}
