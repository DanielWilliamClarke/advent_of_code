const std = @import("std");
const mecha = @import("mecha");

const validate = @import("../util/validate.zig").validate;

pub const input_path = "inputs/practice/day03x2020.txt";
pub const example_path = "inputs/practice/day03x2020_example.txt";

const SpaceEntity = enum { open, tree };

fn charToSpace(ch: u8) SpaceEntity {
    return switch (ch) {
        '.' => .open,
        '#' => .tree,
        else => unreachable,
    };
}

const spaceParser = mecha
    .oneOf(.{ mecha.ascii.char('.'), mecha.ascii.char('#') }) // match one space
    .map(charToSpace);

const rowParser = mecha.many(spaceParser, .{});

const Slope = struct { right: usize, down: usize };

const Position = struct {
    x: usize,
    y: usize,

    fn next(self: *Position, grid: *const Grid, slope: Slope) bool {
        self.x = (self.x + slope.right) % grid.width;
        self.y += slope.down;
        return self.y >= grid.height;
    }
};

const Grid = struct {
    grid: [][]SpaceEntity,
    width: usize,
    height: usize,

    pub fn init(grid: [][]SpaceEntity) Grid {
        return Grid{
            .grid = grid,
            .width = if (grid.len == 0) 0 else grid[0].len,
            .height = grid.len,
        };
    }

    pub fn deinit(self: *Grid, alloc: std.mem.Allocator) void {
        for (self.grid) |row| {
            alloc.free(row);
        }
        alloc.free(self.grid);
        self.width = 0;
        self.height = 0;
    }

    pub fn traverseSlopes(self: *const Grid, slopes: []const Slope) i64 {
        var total: i64 = 1;
        for (slopes) |slope| {
            total *= self.countTreesOnSlope(slope);
        }
        return total;
    }

    fn countTreesOnSlope(self: *const Grid, slope: Slope) i64 {
        var count: i64 = 0;
        var pos = Position{ .x = 0, .y = 0 };

        while (!pos.next(self, slope)) {
            if (self.grid[pos.y][pos.x] == .tree) {
                count += 1;
            }
        }

        return count;
    }
};

fn parseGrid(alloc: std.mem.Allocator, lines: []const []const u8) !Grid {
    var grid: std.ArrayList([]SpaceEntity) = .empty;
    defer grid.deinit(alloc);

    for (lines) |line| {
        const row = (try rowParser.parse(alloc, line)).value.ok;
        try grid.append(alloc, row);
    }

    return Grid.init(try grid.toOwnedSlice(alloc));
}

pub fn part1(alloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    var grid = try parseGrid(alloc, lines);
    defer grid.deinit(alloc);

    return grid.traverseSlopes(&[1]Slope{
        .{ .right = 3, .down = 1 },
    });
}

pub fn part2(alloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    var grid = try parseGrid(alloc, lines);
    defer grid.deinit(alloc);

    return grid.traverseSlopes(&[5]Slope{
        .{ .right = 1, .down = 1 },
        .{ .right = 3, .down = 1 },
        .{ .right = 5, .down = 1 },
        .{ .right = 7, .down = 1 },
        .{ .right = 1, .down = 2 },
    });
}

test "day03 2020 part1 example" {
    try validate(part1).with(example_path).equals(7);
}

test "day03 2020 part2 example" {
    try validate(part2).with(example_path).equals(336);
}

test "day03 2020 part1" {
    try validate(part1).with(input_path).equals(289);
}

test "day03 2020 part2" {
    try validate(part2).with(input_path).equals(5522401584);
}
