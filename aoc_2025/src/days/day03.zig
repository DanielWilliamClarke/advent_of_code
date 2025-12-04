const std = @import("std");
const mecha = @import("mecha");
const validate = @import("../util/validate.zig").validate;

pub const input_path = "inputs/day03.txt";
pub const example_path = "inputs/day03_example.txt";

const number = mecha.int(i8, .{ .max_digits = 1 });
const bank: mecha.Parser([]i8) = mecha.many(number, .{});

fn parse(alloc: std.mem.Allocator, lines: []const []const u8) ![][]i8 {
    var banks: std.ArrayList([]i8) = .empty;
    defer {
        for (banks.items) |s| alloc.free(s);
        banks.deinit(alloc);
    }

    for (lines) |line| {
        const parsed = (try bank.parse(alloc, line)).value.ok;
        try banks.append(alloc, parsed);
    }

    return banks.toOwnedSlice(alloc);
}

fn totalJoltage(banks: [][]i8) i64 {
    var joltage: i64 = 0;

    for (banks) |ba| {
        var indez: usize = 0;

        var first: i64 = 0;
        var second: i64 = 0;

        std.debug.print("Bank: ", .{});
        for (ba) |bat| {
            std.debug.print("{d}", .{bat});
        }

        // start to end - 1
        for (0..(ba.len - 1)) |i| {
            if (ba[i] > first) {
                first = ba[i];
                indez = i;
            }
        }

        // index + 1 to end
        for ((indez + 1)..ba.len) |i| {
            if (ba[i] > second) {
                second = ba[i];
            }
        }

        std.debug.print(" LJ: {d}{d} \n", .{ first, second });

        joltage += first * 10 + second;
    }

    return joltage;
}

pub fn part1(alloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    const banks = try parse(alloc, lines);
    defer {
        for (banks) |s| alloc.free(s);
        alloc.free(banks);
    }

    return totalJoltage(banks);
}

pub fn part2(_: std.mem.Allocator, _: []const []const u8) !i64 {
    return 0;
}

test "day03 part1 example" {
    try validate(part1).with(example_path).equals(357);
}

test "day03 part1" {
    try validate(part1).with(input_path).equals(17376);
}

// test "day03 part2 example" {
//     try validate(part2).with(example_path).equals(0);
// }

// test "day03 part2" {
//     try validate(part2).with(input_path).equals(0);
// }
