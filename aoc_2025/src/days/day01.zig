const std = @import("std");
const validate = @import("../util/validate.zig").validate;

pub const input_path = "inputs/day00.txt";
pub const example_path = "inputs/day00_example.txt";

pub fn part1(_: std.mem.Allocator, _: []const []const u8) !i64 {
    return 0;
}

pub fn part2(_: std.mem.Allocator, _: []const []const u8) !i64 {
    return 0;
}

test "day01 example" {
    try validate(example_path, part1, 0);
}

test "day01 part1" {
    try validate(input_path, part1, 0);
}

test "day01 part2" {
    try validate(input_path, part2, 0);
}
