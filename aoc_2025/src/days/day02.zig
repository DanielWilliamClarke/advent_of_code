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

fn allChunksEqual(id_str: []u8, divisions: usize) !bool {
    const len = id_str.len;
    // Must split evenly into `divisions` chunks
    if (len % divisions != 0) return false;

    const chunk_len = len / divisions;

    // First chunk is the reference
    const first = id_str[0..chunk_len];

    // Compare every other chunk to the first
    var start: usize = chunk_len;
    // std.debug.print("id {s} \n", .{id_str});

    while (start < len) : (start += chunk_len) {
        const chunk = id_str[start .. start + chunk_len];
        // std.debug.print("part {s} ", .{chunk});
        if (!std.mem.eql(u8, first, chunk)) {
            return false;
        }
    }

    // std.debug.print("\nMATCH {s} \n", .{id_str});

    return true;
}

fn detect_invalid_ids(ranges: []Range, atLeastTwice: bool) !i64 {
    var total: i64 = 0;

    for (ranges) |r| {
        var id = r.start;
        while (id <= r.end) : (id += 1) {
            var buf: [32]u8 = undefined;
            const id_str = try std.fmt.bufPrint(&buf, "{}", .{id});

            const maxDivisions = if (atLeastTwice) id_str.len else 2;

            for (2..maxDivisions + 1) |d| {
                if (try allChunksEqual(id_str, d)) {
                    total += id;
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
