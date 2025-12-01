const std = @import("std");
const validate = @import("../util/validate.zig").validate;

const mecha = @import("mecha");

pub const input_path = "inputs/day01.txt";
pub const example_path = "inputs/day01_example.txt";

const MAX = 99;

const Turn = struct {
    dir: u8,
    distance: i64,
};

fn toTurn(t: Turn) i64 {
    return switch (t.dir) {
        'L' => -t.distance,
        else => t.distance,
    };
}

const direction = mecha
    .oneOf(.{ mecha.ascii.char('L'), mecha.ascii.char('R') });
const number = mecha.int(i64, .{ .max_digits = 3 });

const turn =
    mecha
        .combine(.{ direction, number })
        .map(mecha.toStruct(Turn))
        .map(toTurn);

pub fn parse(alloc: std.mem.Allocator, lines: []const []const u8) ![]i64 {
    var turns: std.ArrayList(i64) = .empty;
    defer turns.deinit(alloc);

    if (lines.len > 1) {
        for (lines) |line| {
            const parsed = (try turn.parse(alloc, line)).value.ok;
            try turns.append(alloc, parsed);
        }
    }

    return turns.toOwnedSlice(alloc);
}

pub fn turnSafeDial(turns: []i64) i64 {
    var zeros: i64 = 0;
    var position: i64 = 50;

    for (turns) |t| {
        //std.debug.print("Turn {} Position {}\n", .{ t, position });
        position = @mod(position + t, MAX + 1); // to be 0 - 99 inclusive
        if (position == 0) {
            zeros += 1;
        }
    }

    return zeros;
}

pub fn turnSafeDialMethod0x434C49434B(turns: []i64) i64 {
    var zeros: i64 = 0;
    var position: i64 = 50;

    for (turns) |t| {
        const delta: i64 = if (t > 0) 1 else -1;
        for (0..@intCast(@abs(t))) |_| {
            position = @mod(position + delta, MAX + 1);
            if (position == 0) {
                zeros += 1;
            }
        }
    }

    return zeros;
}

pub fn part1(alloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    const turns = try parse(alloc, lines);
    defer alloc.free(turns);

    return turnSafeDial(turns);
}

pub fn part2(alloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    const turns = try parse(alloc, lines);
    defer alloc.free(turns);

    return turnSafeDialMethod0x434C49434B(turns);
}

test "day01 part 1 example" {
    try validate(part1).with(example_path).equals(3);
}

test "day01 part1" {
    try validate(part1).with(input_path).equals(1102);
}

test "day01 part 2 example" {
    try validate(part2).with(example_path).equals(6);
}

test "day01 part2" {
    try validate(part2).with(input_path).equals(6175);
}
