const std = @import("std");
const mecha = @import("mecha");
const validate = @import("../util/validate.zig").validate;

pub const input_path = "inputs/day09.txt";
pub const example_path = "inputs/day09_example.txt";

const Coord = struct {
    x: i64,
    y: i64,
};

const comma = mecha.ascii.char(',').discard();
const number = mecha.int(i64, .{});

const coordParser: mecha.Parser(Coord) = mecha
    .manyN(number, 2, .{ .separator = comma })
    .map(mecha.toStruct(Coord));

fn parse(alloc: std.mem.Allocator, lines: []const []const u8) ![]Coord {
    var coords: std.ArrayList(Coord) = .empty;
    defer coords.deinit(alloc);

    for (lines) |line| {
        const box: Coord = (try coordParser.parse(alloc, line)).value.ok;
        try coords.append(alloc, box);
    }

    return coords.toOwnedSlice(alloc);
}

fn makeMemo(alloc: std.mem.Allocator, length: usize) ![][]?bool {
    const memo = try alloc.alloc([]?bool, length * 2);

    for (memo) |*r| {
        r.* = try alloc.alloc(?bool, length * 2);
        for (r.*) |*c| {
            c.* = false;
        }
    }

    return memo;
}

fn findLargestRectange(alloc: std.mem.Allocator, coords: []Coord) !i64 {
    var max: i64 = 0;

    const memo = try makeMemo(alloc, coords.len);
    defer {
        for (memo) |m| alloc.free(m);
        alloc.free(memo);
    }

    for (0..(coords.len - 1)) |i| {
        for ((i + 1)..coords.len) |j| {
            if (memo[i][j].? or memo[j][i].?) {
                continue;
            }
            memo[i][j] = true;

            const a = coords[i];
            const b = coords[j];

            // area = h * w;
            const w = @abs(b.x - a.x) + 1;
            const h = @abs(b.y - a.y) + 1;
            const area = @as(i64, @intCast(w * h));

            // std.debug.print("A: {}, B: {}, area: {d}\n", .{ a, b, area });

            if (area > max) {
                max = area;
            }
        }
    }

    return max;
}

pub fn part1(alloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    const coords = try parse(alloc, lines);
    defer alloc.free(coords);

    return try findLargestRectange(alloc, coords);
}

pub fn part2(_: std.mem.Allocator, _: []const []const u8) !i64 {
    return 0;
}

test "day09 part1 example" {
    try validate(part1).with(example_path).equals(50);
}

test "day09 part1" {
    try validate(part1).with(input_path).equals(4755278336);
}

// test "day09 part2 example" {
//     try validate(part2).with(example_path).equals(0);
// }

// test "day09 part2" {
//     try validate(part2).with(input_path).equals(0);
// }
