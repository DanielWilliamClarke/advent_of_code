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

fn parse(alloc: std.mem.Allocator, lines: []const []const u8) ![]Range {
    return (try rangesParser.parse(alloc, lines[0])).value.ok;
}

fn all_chunks_equal(id_str: []u8, divisions: usize) !bool {
    if (id_str.len % divisions != 0) {
        return false;
    }

    const chunk_len = id_str.len / divisions;
    const first = id_str[0..chunk_len];

    // compare chunks
    var start: usize = chunk_len;
    while (start < id_str.len) : (start += chunk_len) {
        const current = id_str[start .. start + chunk_len];
        if (!std.mem.eql(u8, first, current)) {
            return false;
        }
    }

    return true;
}

fn detect_invalid_ids(ranges: []Range, testAllDivisions: bool) !i64 {
    var total: i64 = 0;

    for (ranges) |r| {
        for (@intCast(r.start)..@intCast(r.end + 1)) |id| {
            var buf: [32]u8 = undefined;
            const id_str = try std.fmt.bufPrint(&buf, "{}", .{id});
            const maxDivisions = if (testAllDivisions) id_str.len else 2;

            for (2..maxDivisions + 1) |d| {
                if (try all_chunks_equal(id_str, d)) {
                    total += @intCast(id);
                    break; // leave loop on first match
                }
            }
        }
    }

    return total;
}

pub fn part1(alloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    const ranges = try parse(alloc, lines);
    defer alloc.free(ranges);

    return try detect_invalid_ids(ranges, false);
}

pub fn part2(alloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    const ranges = try parse(alloc, lines);
    defer alloc.free(ranges);

    return try detect_invalid_ids(ranges, true);
}

test "day02 part1 example" {
    try validate(part1).with(example_path).equals(1227775554);
}

test "day02 part1" {
    try validate(part1).with(input_path).equals(16793817782);
}

test "day02 part2 example" {
    try validate(part2).with(example_path).equals(4174379265);
}

test "day02 part2" {
    try validate(part2).with(input_path).equals(27469417404);
}
