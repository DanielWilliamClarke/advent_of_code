const std = @import("std");
const mecha = @import("mecha");
const validate = @import("../util/validate.zig").validate;

pub const input_path = "inputs/day09.txt";
pub const example_path = "inputs/day09_example.txt";

const Coord = struct {
    x: i64,
    y: i64,
};

pub const Segment = struct {
    p1: Coord,
    p2: Coord,
};

pub const Rect = struct {
    x1: i64,
    x2: i64,
    y1: i64,
    y2: i64,
    area: i64,
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

fn buildPerimeter(
    alloc: std.mem.Allocator,
    coords: []const Coord,
) ![]Segment {
    var segments = try alloc.alloc(Segment, coords.len);

    var i: usize = 0;
    while (i < coords.len) : (i += 1) {
        segments[i] = .{
            .p1 = coords[if (i == 0) coords.len - 1 else i - 1], // connect start to end
            .p2 = coords[i],
        };
    }

    return segments;
}

fn generateRectangles(
    alloc: std.mem.Allocator,
    coords: []const Coord,
) ![]Rect {
    var list: std.ArrayList(Rect) = .empty;

    var i: usize = 0;
    while (i < coords.len) : (i += 1) {
        var j: usize = i + 1;
        while (j < coords.len) : (j += 1) {
            const rt1 = coords[i];
            const rt2 = coords[j];

            const x1 = @min(rt1.x, rt2.x);
            const x2 = @max(rt1.x, rt2.x);
            const y1 = @min(rt1.y, rt2.y);
            const y2 = @max(rt1.y, rt2.y);

            const w = (x2 - x1 + 1);
            const h = (y2 - y1 + 1);
            const area = w * h;

            try list.append(alloc, .{ .x1 = x1, .x2 = x2, .y1 = y1, .y2 = y2, .area = area });
        }
    }

    return list.toOwnedSlice(alloc);
}

fn sortRectanglesByAreaDesc(rects: []Rect) void {
    std.sort.block(Rect, rects, {}, struct {
        fn lessThan(_: void, a: Rect, b: Rect) bool {
            return a.area > b.area; // largest first
        }
    }.lessThan);
}

fn rectRespectsPerimeter(rect: Rect, perimeter: []const Segment) bool {
    for (perimeter) |segment| {
        const p1 = segment.p1;
        const p2 = segment.p2;

        const min_x = @min(p1.x, p2.x);
        const max_x = @max(p1.x, p2.x);
        const min_y = @min(p1.y, p2.y);
        const max_y = @max(p1.y, p2.y);

        const is_left = rect.x2 <= min_x;
        const is_right = rect.x1 >= max_x;
        const above = rect.y2 <= min_y;
        const below = rect.y1 >= max_y;

        if (!(is_left or is_right or above or below)) {
            return false;
        }
    }

    return true;
}

pub fn findLargestRectangleInside(
    alloc: std.mem.Allocator,
    coords: []const Coord,
) !i64 {
    if (coords.len < 2) {
        return 0;
    }

    const perimeter = try buildPerimeter(alloc, coords);
    defer alloc.free(perimeter);

    const rects = try generateRectangles(alloc, coords);
    defer alloc.free(rects);

    sortRectanglesByAreaDesc(rects);

    // First rect that satisfies perimeter rules is the biggest, since they are sorted
    for (rects) |rect| {
        if (rectRespectsPerimeter(rect, perimeter)) {
            return rect.area;
        }
    }

    return 0;
}

fn findLargestRectange(coords: []Coord) !i64 {
    var max: i64 = 0;

    for (0..(coords.len - 1)) |i| {
        for ((i + 1)..coords.len) |j| {
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

    return try findLargestRectange(coords);
}

pub fn part2(alloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    const coords = try parse(alloc, lines);
    defer alloc.free(coords);

    return try findLargestRectangleInside(alloc, coords);
}

test "day09 part1 example" {
    try validate(part1).with(example_path).equals(50);
}

test "day09 part1" {
    try validate(part1).with(input_path).equals(4755278336);
}

test "day09 part2 example" {
    try validate(part2).with(example_path).equals(24);
}

test "day09 part2" {
    try validate(part2).with(input_path).equals(1534043700);
}
