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

fn makeMemo(
    alloc: std.mem.Allocator,
    grid: [][]Cell,
) ![][]?i64 {
    const height = grid.len;
    const width = grid[0].len;

    const memo = try alloc.alloc([]?u64, height);

    for (memo) |*row| {
        row.* = try alloc.alloc(?u64, width);
        for (row.*) |*cell| {
            cell.* = null;
        }
    }

    return memo;
}

fn drawGrid(grid: *[][]Cell) void {
    for (grid.*) |row| {
        for (row) |cell| {
            std.debug.print("{c}", .{cellToChar(cell)});
        }
        std.debug.print("\n", .{});
    }
}

fn simulateTachyonBeams(grid: *[][]Cell, curr: Coord) i64 {
    // bounds check and exit clause
    if (curr.x < 0 or curr.x >= grid.*[0].len or curr.y < 0 or curr.y >= grid.*.len) {
        return 0;
    }

    const next = Coord{ .x = curr.x, .y = curr.y + 1 };

    return switch (grid.*[curr.y][curr.x]) {
        .beam, .split => 0, // already visited, no new splits from here
        .start => simulateTachyonBeams(grid, next),
        .space => blk: {
            // turn space into beam to "visit" space
            grid.*[curr.y][curr.x] = .beam;

            // propagate beam
            break :blk simulateTachyonBeams(grid, next);
        },
        .splitter => blk: {
            const nl = Coord{ .x = curr.x - 1, .y = curr.y };
            const nr = Coord{ .x = curr.x + 1, .y = curr.y };

            const nextLeft = grid.*[nl.y][nl.x];
            const nextRight = grid.*[nr.y][nr.x];

            var did_split: i64 = 0;

            // if a beam can be created it can be "split"
            // NAND: !(both already beam)
            if (!(nextLeft == .beam and nextRight == .beam)) {
                grid.*[curr.y][curr.x] = .split;
                did_split = 1;
            }

            const left_splits = simulateTachyonBeams(grid, nl);
            const right_splits = simulateTachyonBeams(grid, nr);

            break :blk did_split + left_splits + right_splits;
        },
    };
}

fn simulateQuantumTachyonBeams(
    grid: [][]Cell,
    curr: Coord,
    memo: [][]?i64,
) i64 {
    // Out of bounds = one complete timeline
    if (curr.x < 0 or curr.x >= grid[0].len or curr.y < 0 or curr.y >= grid.len) {
        return 1;
    }

    // Check the memo to not do recomputation
    if (memo[curr.y][curr.x]) |cached| {
        return cached;
    }

    const result = switch (grid[curr.y][curr.x]) {
        .split, .beam => 0, // should not be encoutnered in this version
        .start, .space => blk: {
            // Just move down
            const next = Coord{ .x = curr.x, .y = curr.y + 1 };
            break :blk simulateQuantumTachyonBeams(grid, next, memo);
        },
        .splitter => blk: {
            // Time splits: left and right in the *same row*
            const left = Coord{ .x = curr.x - 1, .y = curr.y };
            const right = Coord{ .x = curr.x + 1, .y = curr.y };

            const left_paths = simulateQuantumTachyonBeams(grid, left, memo);
            const right_paths = simulateQuantumTachyonBeams(grid, right, memo);

            break :blk left_paths + right_paths;
        },
    };

    memo[curr.y][curr.x] = result;
    return result;
}

pub fn part1(alloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    var grid = try parse(alloc, lines);
    defer {
        for (grid) |row| alloc.free(row);
        alloc.free(grid);
    }

    // find starting point;
    const start = findStart(&grid);
    const count = simulateTachyonBeams(&grid, start);

    // drawGrid(&grid);
    return count;
}

pub fn part2(alloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    var grid = try parse(alloc, lines);
    defer {
        for (grid) |row| alloc.free(row);
        alloc.free(grid);
    }

    // find starting point;
    const start = findStart(&grid);
    const memo = try makeMemo(alloc, grid);
    defer {
        for (memo) |row| alloc.free(row);
        alloc.free(memo);
    }

    const count = simulateQuantumTachyonBeams(grid, start, memo);

    // drawGrid(&grid);
    return count;
}

test "day07 part1 example" {
    try validate(part1).with(example_path).equals(21);
}

test "day07 part1" {
    try validate(part1).with(input_path).equals(1499);
}

test "day07 part2 example" {
    try validate(part2).with(example_path).equals(40);
}

test "day07 part2" {
    try validate(part2).with(input_path).equals(24743903847942);
}
