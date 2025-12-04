const std = @import("std");
const mecha = @import("mecha");
const validate = @import("../util/validate.zig").validate;

pub const input_path = "inputs/day03.txt";
pub const example_path = "inputs/day03_example.txt";

const number = mecha.int(i8, .{ .max_digits = 1 });
const bankParser: mecha.Parser([]i8) = mecha.many(number, .{});

fn parse(alloc: std.mem.Allocator, lines: []const []const u8) ![][]i8 {
    var banks: std.ArrayList([]i8) = .empty;
    defer {
        for (banks.items) |s| alloc.free(s);
        banks.deinit(alloc);
    }

    for (lines) |line| {
        const parsed = (try bankParser.parse(alloc, line)).value.ok;
        try banks.append(alloc, parsed);
    }

    return banks.toOwnedSlice(alloc);
}

fn totalJoltage(banks: [][]i8, comptime batteries: usize) i64 {
    var joltage: i64 = 0;

    for (banks) |bank| {
        // std.debug.print("Bank: ", .{});
        // for (bank) |bat| {
        //     std.debug.print("{d}", .{bat});
        // }

        var enabled: [batteries]i8 = [_]i8{0} ** batteries;

        var start: usize = 0;
        for (0..batteries) |pos| {
            const remaining = batteries - pos;
            const last_start = bank.len - remaining; // inclusive start limit

            var best_val: i8 = 0;
            var best_idx: usize = start;

            for (start..(last_start + 1)) |i| {
                if (bank[i] > best_val) {
                    best_val = bank[i];
                    best_idx = i;
                }
            }

            enabled[pos] = best_val;
            start = best_idx + 1; // next digit must come after this index
        }

        // std.debug.print(" joltage:", .{});
        for (enabled, 0..) |battery, i| {
            // std.debug.print("{d}", .{battery});

            // leftmost digit uses 10^(len-1), rightmost uses 10^0
            const exp: i64 = @intCast(enabled.len - 1 - i);
            const pow10 = std.math.pow(i64, 10, exp);
            joltage += @as(i64, battery) * pow10;
        }
        // std.debug.print("\n", .{});
    }

    return joltage;
}

pub fn part1(alloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    const banks = try parse(alloc, lines);
    defer {
        for (banks) |s| alloc.free(s);
        alloc.free(banks);
    }

    return totalJoltage(banks, 2);
}

pub fn part2(alloc: std.mem.Allocator, lines: []const []const u8) !i64 {
    const banks = try parse(alloc, lines);
    defer {
        for (banks) |s| alloc.free(s);
        alloc.free(banks);
    }

    return totalJoltage(banks, 12);
}

test "day03 part1 example" {
    try validate(part1).with(example_path).equals(357);
}

test "day03 part1" {
    try validate(part1).with(input_path).equals(17376);
}

test "day03 part2 example" {
    try validate(part2).with(example_path).equals(3121910778619);
}

test "day03 part2" {
    try validate(part2).with(input_path).equals(172119830406258);
}
