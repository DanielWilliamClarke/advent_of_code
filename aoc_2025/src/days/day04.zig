const std = @import("std");
const mecha = @import("mecha");
const validate = @import("../util/validate.zig").validate;

pub const input_path = "inputs/day04.txt";
pub const example_path = "inputs/day04_example.txt";

const Cell = enum { open, paper };

fn charToCell(ch: u8) Cell {
    return switch (ch) {
        '.' => .open,
        '@' => .paper,
        else => unreachable,
    };
}

const cellParser = mecha
    .oneOf(.{ mecha.ascii.char('.'), mecha.ascii.char('@') }) // match one space
    .map(charToCell);

const rowParser = mecha.many(cellParser, .{});

fn parse(alloc: std.mem.Allocator, lines: []const []const u8) ![][]Cell {
    var grid: std.ArrayList([]Cell) = .empty;
    defer grid.deinit(alloc);

    for (lines) |line| {
        const row: []Cell = (try rowParser.parse(alloc, line)).value.ok;
        try grid.append(alloc, row);
    }

    return grid.toOwnedSlice(alloc);
}

fn neighborRange(idx: usize, max: usize) struct { start: usize, end: usize } {
    const start = if (idx == 0) 0 else idx - 1;
    const stop = @min(idx + 1, max);
    return .{ .start = start, .end = stop + 1 }; // end is exclusive
}

fn countAccessibleCells(grid: [][]Cell, comptime shouldRemove: bool) i64 {
    var count: i64 = 0;
    var removed: i64 = 0;

    const height = grid.len;
    const width = grid[0].len;

    for (0..height) |y| {
        for (0..width) |x| {
            // if not paper carry on
            if (grid[y][x] == .open) {
                continue;
            }

            // check window
            var filled: i64 = 0;
            const yrange = neighborRange(y, height - 1);
            const xrange = neighborRange(x, width - 1);

            for (yrange.start..yrange.end) |yr| {
                for (xrange.start..xrange.end) |xr| {
                    if (yr == y and xr == x) continue;

                    // check neighbough is papaer
                    if (grid[yr][xr] == .paper) {
                        filled += 1;
                    }
                }
            }

            if (filled < 4) {
                count += 1;

                if (shouldRemove) {
                    removed += 1;
                    grid[y][x] = .open;
                }
            }
        }
    }

    // finally some recursion
    if (shouldRemove and removed > 0) {
        count += countAccessibleCells(grid, shouldRemove);
    }

    return count;
}

pub fn part1(alloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    const grid = try parse(alloc, lines);
    defer {
        for (grid) |c| alloc.free(c);
        alloc.free(grid);
    }

    return countAccessibleCells(grid, false);
}

pub fn part2(alloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    const grid = try parse(alloc, lines);
    defer {
        for (grid) |c| alloc.free(c);
        alloc.free(grid);
    }

    return countAccessibleCells(grid, true);
}

test "day04 part1 example" {
    try validate(part1).with(example_path).equals(13);
}

test "day04 part1" {
    try validate(part1).with(input_path).equals(1569);
}

test "day04 part2 example" {
    try validate(part2).with(example_path).equals(43);
}

test "day04 part2" {
    try validate(part2).with(input_path).equals(9280);
}
