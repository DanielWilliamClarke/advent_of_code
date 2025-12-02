const std = @import("std");
const mecha = @import("mecha");
const validate = @import("../util/validate.zig").validate;

pub const input_path = "inputs/day02.txt";
pub const example_path = "inputs/day02_example.txt";

const Range = struct {
    start: i64,
    end: i64,
};

const delimiter = mecha.ascii.char(',').discard();
const dash = mecha.ascii.char('-').discard();
const number = mecha.int(i64, .{});

const range =
    mecha
        .combine(.{ number, dash, number })
        .map(mecha.toStruct(Range));

const rangesParser: mecha.Parser([]Range) = mecha.many(range, .{ .separator = delimiter });

pub fn parse(alloc: std.mem.Allocator, lines: []const []const u8) ![]Range {
    return (try rangesParser.parse(alloc, lines[0])).value.ok;
}

pub fn detect_invalid_ids(ranges: []Range) !i64 {
    var total: i64 = 0;

    for (ranges) |r| {
        // std.debug.print("Start {d}, End {d}\n", .{ r.start, r.end });
        for (@intCast(r.start)..@intCast(r.end + 1)) |index| {
            const id: i64 = @intCast(index);
            var buf: [32]u8 = undefined;
            const id_str: []u8 = try std.fmt.bufPrint(&buf, "{}", .{id});
            if ((id_str.len % 2) != 0) {
                continue;
            }

            const mid = id_str.len / 2;
            const left = try std.fmt.parseInt(i64, id_str[0..mid], 10);
            const right = try std.fmt.parseInt(i64, id_str[mid..], 10);

            if (left == right) {
                // std.debug.print("MATCH {d}{d} \n", .{ left, right });
                total += id;
            }
        }
    }

    return total;
}

pub fn part1(alloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    const ranges = try parse(alloc, lines);
    defer alloc.free(ranges);

    return try detect_invalid_ids(ranges);
}

pub fn part2(_: std.mem.Allocator, _: []const []const u8) !i64 {
    return 0;
}

test "day02 part1 example" {
    try validate(part1).with(example_path).equals(1227775554);
}

test "day02 part1" {
    try validate(part1).with(input_path).equals(16793817782);
}

// test "day02 part2 example" {
//     try validate(part2).with(example_path).equals(0);
// }

// test "day02 part2" {
//     try validate(part2).with(input_path).equals(0);
// }
