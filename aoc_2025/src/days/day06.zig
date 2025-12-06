const std = @import("std");
const mecha = @import("mecha");
const validate = @import("../util/validate.zig").validate;

pub const input_path = "inputs/day06.txt";
pub const example_path = "inputs/day06_example.txt";

const Op = enum { plus, mult };

const ColumnBlock = struct {
    op: Op,
    rows: [][]u8,
};

fn parseCepholapodBlocks(
    alloc: std.mem.Allocator,
    lines: []const []const u8,
) ![]ColumnBlock {
    const ops_line = lines[lines.len - 1];
    const rows = lines[0 .. lines.len - 1];

    // Find all operator positions and ops
    var op_count: usize = 0;
    for (ops_line) |ch| {
        if (ch == '+' or ch == '*') {
            op_count += 1;
        }
    }
    if (op_count == 0) {
        return try alloc.alloc(ColumnBlock, 0);
    }

    var op_positions = try alloc.alloc(usize, op_count);
    var op_values = try alloc.alloc(Op, op_count);
    errdefer {
        alloc.free(op_positions);
        alloc.free(op_values);
    }

    var idx: usize = 0;
    for (ops_line, 0..) |ch, i| {
        switch (ch) {
            '+' => {
                op_positions[idx] = i;
                op_values[idx] = .plus;
                idx += 1;
            },
            '*' => {
                op_positions[idx] = i;
                op_values[idx] = .mult;
                idx += 1;
            },
            else => {},
        }
    }

    // Find maximum width across all rows
    var max_width: usize = ops_line.len;
    for (rows) |row| {
        if (row.len > max_width) {
            max_width = row.len;
        }
    }

    // Build blocks
    var blocks = try alloc.alloc(ColumnBlock, op_count);

    var k: usize = 0;
    while (k < op_count) : (k += 1) {
        const start = op_positions[k];
        const end = if (k + 1 < op_count) op_positions[k + 1] else max_width;
        const span_width = end - start;

        // Allocate rows for this block
        var block_rows = try alloc.alloc([]u8, rows.len);

        for (rows, 0..) |row, r| {
            block_rows[r] = try alloc.alloc(u8, span_width);
            // fill with spaces
            @memset(block_rows[r], ' ');

            // copy whatever slice is available in the source row
            if (start < row.len) {
                const src_end = @min(end, row.len);
                const copy_len = src_end - start;
                @memcpy(block_rows[r][0..copy_len], row[start..src_end]);
            }
        }

        blocks[k] = .{
            .op = op_values[k],
            .rows = block_rows,
        };
    }

    return blocks;
}

fn trimAndParseNumber(s: []const u8) !i64 {
    const trimmed = std.mem.trim(u8, s, &std.ascii.whitespace);
    return std.fmt.parseInt(i64, trimmed, 10);
}

fn solveHumanMath(parentAlloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    var arena = std.heap.ArenaAllocator.init(parentAlloc);
    defer arena.deinit();
    const alloc = arena.allocator();

    const columns = try parseCepholapodBlocks(alloc, lines);
    defer alloc.free(columns);

    const totals = try alloc.alloc(i64, columns.len);
    defer alloc.free(totals);

    // init values based on op
    for (columns, 0..) |block, index| {
        totals[index] = switch (block.op) {
            .plus => 0,
            .mult => 1,
        };
    }

    for (columns, 0..) |block, index| {
        for (block.rows) |row| {
            const humanValue = try trimAndParseNumber(row);
            switch (block.op) {
                .plus => totals[index] += humanValue,
                .mult => totals[index] *= humanValue,
            }
        }
    }

    // Sum totals
    var sum: i64 = 0;
    for (totals) |t| {
        sum += t;
    }

    return sum;
}

fn solveCephalopodMath(parentAlloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    var arena = std.heap.ArenaAllocator.init(parentAlloc);
    defer arena.deinit();
    const alloc = arena.allocator();

    const columns = try parseCepholapodBlocks(alloc, lines);
    defer alloc.free(columns);

    const totals = try alloc.alloc(i64, columns.len);
    defer alloc.free(totals);

    // init values based on op
    for (columns, 0..) |block, index| {
        totals[index] = switch (block.op) {
            .plus => 0,
            .mult => 1,
        };
    }

    for (columns, 0..) |block, index| {
        for (0..block.rows[0].len) |i| {
            // If all elements are a space just ignore, we grab columns with trailing spaces
            var allSpaces = true;
            for (0..(block.rows.len)) |j| {
                if (block.rows[j][i] != ' ') {
                    allSpaces = false;
                }
            }
            if (allSpaces) {
                continue; // move to next row / column
            }

            // Pick values columnwise
            var rawCephalopodValue = try alloc.alloc(u8, block.rows.len);
            for (0..(block.rows.len)) |j| {
                rawCephalopodValue[j] = block.rows[j][i];
            }

            // do the human math part
            const cephalopodValue = try trimAndParseNumber(rawCephalopodValue);
            switch (block.op) {
                .plus => totals[index] += cephalopodValue,
                .mult => totals[index] *= cephalopodValue,
            }
        }
    }

    var sum: i64 = 0;
    for (totals) |t| {
        sum += t;
    }

    return sum;
}

pub fn part1(alloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    return try solveHumanMath(alloc, lines);
}

pub fn part2(alloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    return try solveCephalopodMath(alloc, lines);
}

test "day06 part1 example" {
    try validate(part1).with(example_path).equals(4277556);
}

test "day06 part1" {
    try validate(part1).with(input_path).equals(6343365546996);
}

test "day06 part2 example" {
    try validate(part2).with(example_path).equals(3263827);
}

test "day06 part2" {
    try validate(part2).with(input_path).equals(11136895955912);
}
