const std = @import("std");
const mecha = @import("mecha");
const validate = @import("../util/validate.zig").validate;

pub const input_path = "inputs/day07.txt";
pub const example_path = "inputs/day07_example.txt";

const Cell = enum { start, splitter, split, space, beam };

fn charToCell(ch: u8) Cell {
    return switch (ch) {
        'S' => .start,
        '^' => .splitter,
        '+' => .split,
        '.' => .space,
        '|' => .beam,
        else => unreachable,
    };
}

fn cellToChar(c: Cell) u8 {
    return switch (c) {
        .start => 'S',
        .splitter => '^',
        .split => '+',
        .space => '.',
        .beam => '|',
    };
}

const cellParser = mecha
    .oneOf(.{ mecha.ascii.char('S'), mecha.ascii.char('^'), mecha.ascii.char('.'), mecha.ascii.char('|') }) // match one space
    .map(charToCell);

const rowParser: mecha.Parser([]Cell) = mecha.many(cellParser, .{});

fn parse(alloc: std.mem.Allocator, lines: []const []const u8) ![][]Cell {
    var grid: std.ArrayList([]Cell) = .empty;
    defer grid.deinit(alloc);

    for (lines) |line| {
        const row: []Cell = (try rowParser.parse(alloc, line)).value.ok;
        try grid.append(alloc, row);
    }

    return grid.toOwnedSlice(alloc);
}

const Coord = struct { x: usize, y: usize };

fn findStart(grid: *[][]Cell) Coord {
    return blk: {
        for (grid.*, 0..) |row, y| {
            for (row, 0..) |cell, x| {
                if (cell == .start) {
                    break :blk .{ .x = x, .y = y };
                }
            }
        }
        @panic("Start not found");
    };
}

fn simulateTachyonBeam(grid: *[][]Cell, curr: Coord, count: *i64) void {
    // bounds check and exit clause
    if (curr.x < 0 or curr.x >= grid.*[0].len or curr.y < 0 or curr.y >= grid.*.len) {
        return;
    }

    const next = Coord{ .x = curr.x, .y = curr.y + 1 };

    switch (grid.*[curr.y][curr.x]) {
        .beam => {
            // beams cant intersect so we've already visited this cell, so move on
        },
        .split => {
            // just for debug, but does nothing since its already been used
        },
        .start => {
            // propagate down
            simulateTachyonBeam(grid, next, count);
        },
        .space => {
            // turn space into beam to "visit" space
            grid.*[curr.y][curr.x] = .beam;

            // propagate beam
            simulateTachyonBeam(grid, next, count);
        },
        .splitter => {
            // look ahead to count split before propagating
            const nl = Coord{ .x = curr.x - 1, .y = curr.y };
            const nr = Coord{ .x = curr.x + 1, .y = curr.y };

            const nextLeft = grid.*[nl.y][nl.x];
            const nextRight = grid.*[nr.y][nr.x];

            // if a beam can be created it can be "split",
            // if both are already beam, then we arent not splitting
            // NAND
            if (!(nextLeft == .beam and nextRight == .beam)) {
                grid.*[curr.y][curr.x] = .split;
                count.* += 1;
            }

            // propagate left
            simulateTachyonBeam(grid, nl, count);
            // propagate right
            simulateTachyonBeam(grid, nr, count);
        },
    }
}

fn drawGrid(grid: *[][]Cell) void {
    for (grid.*) |row| {
        for (row) |cell| {
            std.debug.print("{c}", .{cellToChar(cell)});
        }
        std.debug.print("\n", .{});
    }
}

pub fn part1(alloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    var grid = try parse(alloc, lines);
    defer {
        for (grid) |row| alloc.free(row);
        alloc.free(grid);
    }

    // find starting point;
    const start = findStart(&grid);

    var count: i64 = 0;
    simulateTachyonBeam(&grid, start, &count);

    // drawGrid(&grid);
    return count;
}

pub fn part2(_: std.mem.Allocator, _: []const []const u8) !i64 {
    return 0;
}

test "day07 part1 example" {
    try validate(part1).with(example_path).equals(21);
}

test "day07 part1" {
    try validate(part1).with(input_path).equals(1499);
}

// test "day07 part2 example" {
//     try validate(part2).with(example_path).equals(0);
// }

// test "day07 part2" {
//     try validate(part2).with(input_path).equals(0);
// }
